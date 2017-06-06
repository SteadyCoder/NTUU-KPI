//
//  Parser.m
//  TranslatorOne
//
//  Created by Ivan on 5/31/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import "Parser.h"
#import "MyNode.h"
#import "Scanner.h"
#import "NSArray+MutableArrayStart.h"

@interface MyNodeTokenStruct : NSObject

@property (nonatomic, strong) MyNode *node;
@property (nonatomic, strong) NSMutableArray<NSDictionary *> *arrayOfTokens;

- (instancetype)initWithNode:(MyNode *)node andArray:(NSArray *)array;
+ (instancetype)withNode:(MyNode *)aNode andArray:(NSMutableArray<NSDictionary *> *)anArray;

@end

NSString * const kKeyWord = @"KEYWORDS";

@implementation MyNodeTokenStruct

- (instancetype)initWithNode:(MyNode *)aNode andArray:(NSMutableArray<NSDictionary *> *)anArray {
    self = [super init];
    if (self) {
        _node = aNode;
        _arrayOfTokens = anArray;
    }
    return self;
}

+ (instancetype)withNode:(MyNode *)aNode andArray:(NSMutableArray<NSDictionary *> *)anArray {
    return [[MyNodeTokenStruct alloc] initWithNode:aNode andArray:anArray];
}

@end

@implementation Parser

- (instancetype)initWithTokensList:(NSArray<NSDictionary *> *)tokensList {
    self = [super init];
    
    if (self) {
        _listOfTokens = tokensList;
    }
    
    return self;
}

- (MyNodeTokenStruct *)unsigned_const:(NSMutableArray *)tokens {
    MyNodeTokenStruct *result;
    if (tokens && [tokens[0][kTokenKeyNameId] integerValue] >= 300 && [tokens[0][kTokenKeyNameId] integerValue] <= 1000) {
        result = [MyNodeTokenStruct withNode:[MyNode nodeWithData:tokens[0][kTokenKeyNameLexem] rule:@"<unsigned>" parent:nil] andArray:[tokens mutableArrayFromTheStartPoint:1]];
    } else {
        result = [MyNodeTokenStruct withNode:[MyNode errorNodeWithData:tokens[0]] andArray:nil];
    }
    return result;
}

- (MyNodeTokenStruct *)identifier:(NSMutableArray *)tokens {
    NSInteger token = [(tokens[0])[kTokenKeyNameId] integerValue];
    MyNodeTokenStruct *result;
    
    if (tokens.count != 0 && token >= 1000 && token <= 5000) {
        NSData *data = [NSJSONSerialization dataWithJSONObject:tokens[0] options:0 error:0];
        NSString *string = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        result = [MyNodeTokenStruct withNode:[MyNode nodeWithData:string rule:@"<identifier>" parent:nil] andArray:[tokens mutableArrayFromTheStartPoint:1]];
    } else {
        result = [MyNodeTokenStruct withNode:[MyNode errorNodeWithData:tokens[0]] andArray:nil];
    }
    
    return result;
}

- (MyNodeTokenStruct *)operators:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<operator>" parent:nil];
    NSInteger token = [tokens[0][kTokenKeyNameId] integerValue];
    if (token >= 206 && token <= 209) {
        [node addChild:[MyNode nodeWithData:tokens[0][kTokenKeyNameLexem] rule:@"<op>" parent:nil]];
    } else {
        [node addChild:[MyNode errorNodeWithData:tokens[0]]];
    }
    return [MyNodeTokenStruct withNode:node andArray:tokens];
}


// Variable id
- (MyNodeTokenStruct *)variableId:(NSMutableArray *)tokens {
    MyNode *resultNode = [MyNode nodeWithData:nil rule:@"variable_identifier" parent:nil];
    
    MyNodeTokenStruct *temprorary = [self identifier:tokens];
    [resultNode addChild:temprorary.node];
    return [MyNodeTokenStruct withNode:resultNode andArray:temprorary.arrayOfTokens];
}

// Procedure id

- (MyNodeTokenStruct *)procedureId:(NSMutableArray *)tokens {
    MyNode *resultNode = [MyNode nodeWithData:nil rule:@"procedure_identifier" parent:nil];
    MyNodeTokenStruct *temprorary = [self identifier:tokens];
    [resultNode addChild:temprorary.node];
    return [MyNodeTokenStruct withNode:resultNode andArray:temprorary.arrayOfTokens];
}

/////////////////////////////////////////////////////

// Declaration

- (MyNodeTokenStruct *)declaration:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<declaration>" parent:nil];
    MyNodeTokenStruct *result = [self variableId:tokens];
    
    [node addChild:result.node];
    
    if (!result.arrayOfTokens || result.arrayOfTokens.count < 3) {
        return [MyNodeTokenStruct withNode:node andArray:nil];
    } else if ([result.arrayOfTokens[0][kTokenKeyNameId] integerValue] == 202) {
        [node addChild:[MyNode nodeWithData:result.arrayOfTokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        if ([result.arrayOfTokens[1][kTokenKeyNameId] integerValue] == 104 || [result.arrayOfTokens[1][kTokenKeyNameId] integerValue] == 105) {
            [node addChild:[MyNode nodeWithData:result.arrayOfTokens[1][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
            if ([result.arrayOfTokens[2][kTokenKeyNameId] integerValue] == 200) {
                [node addChild:[MyNode nodeWithData:result.arrayOfTokens[2][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
                return [MyNodeTokenStruct withNode:node andArray:[result.arrayOfTokens mutableArrayFromTheStartPoint:3]];
            }
        }
    }
    return [MyNodeTokenStruct withNode:node andArray:nil];
}

// Declaration list

- (MyNodeTokenStruct *)declarationList:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<declaration_list>" parent:nil];
    MyNodeTokenStruct *result;
    if (!tokens.count) {
        [node addChild:[MyNode nodeWithData:nil rule:@"ERROR" parent:nil]];
        result = [MyNodeTokenStruct withNode:node andArray:nil];
    }
    
    MyNodeTokenStruct *temporary = [self declaration:tokens];
    [node addChild:temporary.node];
    
    if (!temporary.arrayOfTokens)
        result = [MyNodeTokenStruct withNode:nil andArray:tokens];
    else {
        temporary = [self declarationList:temporary.arrayOfTokens];
        [node addChild:temporary.node];
        
        result = [MyNodeTokenStruct withNode:node andArray:temporary.arrayOfTokens];
    }
    return result;
}

// Variable declaration
- (MyNodeTokenStruct *)variable_declaration:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<variable_declaration>" parent:nil];
    MyNodeTokenStruct *result;
    if (!tokens) {
        [node addChild:[MyNode nodeWithData:nil rule:@"ERROR" parent:nil]];
        result = [MyNodeTokenStruct withNode:node andArray:nil];
    } else if ([tokens[0][kTokenKeyNameId] integerValue] == 103) {
        [node addChild:[MyNode nodeWithData:tokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        MyNodeTokenStruct *nodeStruct = [self declarationList:[tokens mutableArrayFromTheStartPoint:1]];

        [node addChild:nodeStruct.node];
        result = [MyNodeTokenStruct withNode:node andArray:nodeStruct.arrayOfTokens];
    } else {
        result = [MyNodeTokenStruct withNode:nil andArray:tokens];
    }
    
    return result;
}

- (MyNodeTokenStruct *)comparisonOperator:(NSMutableArray *)tokens {
    MyNodeTokenStruct *result;
    MyNode *node = [MyNode nodeWithData:nil rule:@"<comparison_operator>" parent:nil];
    if ( ([tokens[0][kTokenKeyNameId] integerValue] >= 203 && [tokens[0][kTokenKeyNameId] integerValue] <= 205) || ([tokens[0][kTokenKeyNameId] integerValue] >= 109 && [tokens[0][kTokenKeyNameId] integerValue] <= 111)) {
        [node addChild:[MyNode nodeWithData:tokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        result = [MyNodeTokenStruct withNode:node andArray:[tokens mutableArrayFromTheStartPoint:1]];
    } else {
        [node addChild:[MyNode errorNodeWithData:tokens[0]]];
        result = [MyNodeTokenStruct withNode:node andArray:nil];
    }
    return result;
}

- (MyNodeTokenStruct *)expression:(NSMutableArray *)tokens {
    MyNodeTokenStruct *temporary = [self variableId:tokens];
    if (!temporary.arrayOfTokens) {
        temporary = [self unsigned_const:tokens];
        if (!temporary.arrayOfTokens) {
            temporary = [MyNodeTokenStruct withNode:[MyNode errorNodeWithData:tokens[0]] andArray:nil];
        }
    }
    
    return temporary;
}

// Conditional
- (MyNodeTokenStruct *)conditionalExpression:(NSMutableArray *)tokens {
    MyNode *condition = [MyNode nodeWithData:nil rule:@"<conditional_expression>" parent:nil];
    MyNodeTokenStruct *result;
    
    result = [self expression:tokens];
    [condition addChild:result.node];

    if (result.arrayOfTokens) {
        MyNodeTokenStruct *temporary = [self comparisonOperator:result.arrayOfTokens];
        [condition addChild:temporary.node];
        if (temporary.arrayOfTokens) {
            result = [self expression:temporary.arrayOfTokens];
            [condition addChild:result.node];
            result = [MyNodeTokenStruct withNode:condition andArray:result.arrayOfTokens];
        } else {
            [condition addChild:[MyNode errorNodeWithData:result.arrayOfTokens[0]]];
            result = [MyNodeTokenStruct withNode:condition andArray:nil];
        }
    } else {
        [condition addChild:[MyNode errorNodeWithData:tokens[0]]];
        result = [MyNodeTokenStruct withNode:condition andArray:nil];
    }
    return result;
}

- (MyNodeTokenStruct *)assignOperator:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:tokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil];
    MyNodeTokenStruct *result;
    
    MyNodeTokenStruct *temporary = [self expression:[tokens mutableArrayFromTheStartPoint:1]];
    [node addChild:temporary.node];
    if (temporary.arrayOfTokens) {
        temporary = [self operators:temporary.arrayOfTokens];
        [node addChild:temporary.node];
        if (temporary.arrayOfTokens) {
            MyNodeTokenStruct *temporary_one = [self expression:[temporary.arrayOfTokens mutableArrayFromTheStartPoint:1]];
            [node addChild:temporary_one.node];
            if (temporary_one.arrayOfTokens) {
                result = [MyNodeTokenStruct withNode:node andArray:temporary_one.arrayOfTokens];
            } else {
                [node addChild:[MyNode errorNodeWithData:temporary.arrayOfTokens[0]]];
                result = [MyNodeTokenStruct withNode:node andArray:nil];
            }
        } else {
            [node addChild:[MyNode errorNodeWithData:temporary.arrayOfTokens[0]]];
            result = [MyNodeTokenStruct withNode:node andArray:nil];
        }
    } else {
        [node addChild:[MyNode errorNodeWithData:temporary.arrayOfTokens[0]]];
        result = [MyNodeTokenStruct withNode:node andArray:nil];
    }
    return result;
}

// Statement
- (MyNodeTokenStruct *)statement:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<statement>" parent:nil];
    MyNodeTokenStruct *result;
    
    // 112 - IF
    if ([tokens[0][kTokenKeyNameId] integerValue] == 112) {
        [node addChild:[MyNode nodeWithData:tokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        
        MyNodeTokenStruct *conditionalResult = [self conditionalExpression:[tokens mutableArrayFromTheStartPoint:1]];
        
        [node addChild:conditionalResult.node];
        if (!conditionalResult.arrayOfTokens || [conditionalResult.arrayOfTokens[0][kTokenKeyNameId] integerValue] != 113)
            return [MyNodeTokenStruct withNode:[MyNode errorNodeWithData:conditionalResult.arrayOfTokens[0]] andArray:nil];
        
        [node addChild:[MyNode nodeWithData:conditionalResult.arrayOfTokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        
        MyNodeTokenStruct *statementResult = [self statement_list:[conditionalResult.arrayOfTokens mutableArrayFromTheStartPoint:1]];
        [node addChild:statementResult.node];
        
        // 114 - ELSE
        if ([statementResult.arrayOfTokens[0][kTokenKeyNameId] integerValue] == 114) {
            [node addChild:[MyNode nodeWithData:statementResult.arrayOfTokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
            statementResult = [self statement_list:[statementResult.arrayOfTokens mutableArrayFromTheStartPoint:1]];
            
            [node addChild:statementResult.node];
//            if ([statementResult.arrayOfTokens[1][kTokenKeyNameId] integerValue] == 200) {
//                [node addChild:[MyNode nodeWithData:statementResult.arrayOfTokens[1][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
//            } else {
//                [node addChild:[MyNode errorNodeWithData:statementResult.arrayOfTokens[1]]];
//            }
        }
        
        result = [MyNodeTokenStruct withNode:node andArray:statementResult.arrayOfTokens];
    } else if ([tokens[1][kTokenKeyNameId] integerValue] == 115) {
        MyNode *node = [MyNode nodeWithData:nil rule:@"<assign_operation>" parent:nil];
        MyNodeTokenStruct *variable = [self variableId:tokens];
        
        [node addChild:variable.node];
        //[node addChild:[MyNode nodeWithData:tokens[1][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        if (variable.arrayOfTokens) {
            MyNodeTokenStruct *assignOperator = [self assignOperator:variable.arrayOfTokens];
            
            [node addChild:assignOperator.node];
            result = [MyNodeTokenStruct withNode:node andArray:assignOperator.arrayOfTokens];
        } else {
            [node addChild:[MyNode errorNodeWithData:tokens[0]]];
            result = [MyNodeTokenStruct withNode:node andArray:nil];
        }
        
    } else if (!tokens){
        [node addChild:[MyNode errorNodeWithData:tokens[0]]];
        result = [MyNodeTokenStruct withNode:node andArray:nil];
    }
    
    return result;
}

// Statement operation
- (MyNodeTokenStruct *)statement_list:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<statement_list>" parent:nil];
    MyNodeTokenStruct *result;
    
    MyNodeTokenStruct *statement = [self statement:tokens];
    
    [node addChild:statement.node];
    if (!statement.arrayOfTokens) {
        result = [MyNodeTokenStruct withNode:nil andArray:tokens];
    } else {
        MyNodeTokenStruct *temporary = [self statement_list:statement.arrayOfTokens];
        [node addChild:temporary.node];
        result = [MyNodeTokenStruct withNode:node andArray:temporary.arrayOfTokens];
    }
    return result;
}

// Block opearation
- (MyNodeTokenStruct *)block:(NSMutableArray *)tokens {
    MyNode *node = [MyNode nodeWithData:nil rule:@"<block>" parent:nil];
    MyNodeTokenStruct *structOne = [self variable_declaration:tokens];
    
    [node addChild:structOne.node];
    
    if (!structOne.arrayOfTokens) {
        return [MyNodeTokenStruct withNode:node andArray:nil];
    } else if (structOne.arrayOfTokens.count) {
        if ([structOne.arrayOfTokens[0][kTokenKeyNameId] integerValue] == 101) {
            [node addChild:[MyNode nodeWithData:structOne.arrayOfTokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
            
            MyNodeTokenStruct *structTwo = [self statement_list:[structOne.arrayOfTokens mutableArrayFromTheStartPoint:1]];
            
            [node addChild:structTwo.node];
            if (!structTwo.arrayOfTokens) {
                return [MyNodeTokenStruct withNode:node andArray:nil];
            } else if (structTwo.arrayOfTokens && [structTwo.arrayOfTokens[0][kTokenKeyNameId] integerValue] == 102) {
                [node addChild:[MyNode nodeWithData:structTwo.arrayOfTokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
                if (structTwo.arrayOfTokens.count > 0) {
                    if ([structTwo.arrayOfTokens[1][kTokenKeyNameId] integerValue] == 201) {
                        [node addChild:[MyNode nodeWithData:structTwo.arrayOfTokens[1][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
                    } else {
                        [node addChild:[MyNode errorNodeWithData:structTwo.arrayOfTokens[1]]];
                    }
                } else {
                    [node addChild:[MyNode errorNodeWithData:structTwo.arrayOfTokens[0]]];
                }
                return [MyNodeTokenStruct withNode:node andArray:[structTwo.arrayOfTokens mutableArrayFromTheStartPoint:1]];
            }
        }
    }
    
    [node addChild:[MyNode errorNodeWithData:structOne.arrayOfTokens[0]]];
    return [MyNodeTokenStruct withNode:node andArray:nil];
}

- (void)execute_program {
    MyNode *node = [[MyNode alloc] initWithData:nil aRule:@"<program>" aParent:nil];

    if (self.listOfTokens && [(self.listOfTokens[0])[kTokenKeyNameId] integerValue] == 100) {
        [node addChild:[MyNode nodeWithData:(self.listOfTokens[0])[kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
        MyNodeTokenStruct *tokenStruct = [self procedureId:[self.listOfTokens mutableArrayFromTheStartPoint:1]];
        [node addChild:tokenStruct.node];
        
        if (!tokenStruct.arrayOfTokens || tokenStruct.arrayOfTokens.count == 0) {
            self.tree = node;
            self.listOfTokens = nil;
            [node addChild:[MyNode errorNodeWithData:self.listOfTokens[0]]];
        }
        
        if ([(tokenStruct.arrayOfTokens[0])[kTokenKeyNameId] integerValue] == 200) {
            [node addChild:[MyNode nodeWithData:tokenStruct.arrayOfTokens[0][kTokenKeyNameLexem] rule:kKeyWord parent:nil]];
            MyNodeTokenStruct *blockTokenStruct = [self block:[tokenStruct.arrayOfTokens mutableArrayFromTheStartPoint:1]];
            [node addChild:blockTokenStruct.node];
            
            self.tree = node;
            self.listOfTokens = blockTokenStruct.arrayOfTokens;
        } else {
            [node addChild:[MyNode errorNodeWithData:tokenStruct.arrayOfTokens[0]]];
            self.tree = node;
            self.listOfTokens = tokenStruct.arrayOfTokens;
        }
    } else {
        self.tree = node;
        self.listOfTokens = nil;
    }
}

- (void)resultParserPrint:(MyNode *)tree andOrder:(int)order {
    NSString *data = tree.data;
    
    printf("%*cdata:%s\n %*crule:%s\n\n", order, '\t', [data UTF8String], order, '\t', [tree.rule UTF8String]);
    for (MyNode *node in tree.children) {
        [self resultParserPrint:node andOrder:order+=6];
    }
}



@end
