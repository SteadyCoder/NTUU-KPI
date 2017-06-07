//
//  Parser.h
//  TranslatorOne
//
//  Created by Ivan on 5/31/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const kKeyWord;
extern NSString * const kKeyUnsignedInteger;
extern NSString * const kKeyIdentifier;
extern NSString * const kKeyOperator;
extern NSString * const kKeyOperand;
extern NSString * const kKeyVariableIdentifier;
extern NSString * const kKeyProcedureIdentifier;
extern NSString * const kKeyDeclaration;
extern NSString * const kKeyDeclarationList;
extern NSString * const kKeyVariableDeclaration;
extern NSString * const kKeyComparisonOperator;
extern NSString * const kKeyConditionalExpression;
extern NSString * const kKeyStatement;
extern NSString * const kKeyStatementList;
extern NSString * const kKeyAssignOperation;
extern NSString * const kKeyBlock;
extern NSString * const kKeyProgram;

extern NSString * const kkeyError;

@class MyNode;

@interface MyNodeTokenStruct : NSObject

@property (nonatomic, strong) MyNode *node;
@property (nonatomic, strong) NSMutableArray<NSDictionary *> *arrayOfTokens;

- (instancetype)initWithNode:(MyNode *)node andArray:(NSArray *)array;
+ (instancetype)withNode:(MyNode *)aNode andArray:(NSMutableArray<NSDictionary *> *)anArray;

@end


@interface Parser : NSObject

@property (nonatomic, strong) NSArray<NSDictionary *> *listOfTokens;
@property (nonatomic, strong) MyNode *tree;
@property (nonatomic, strong) NSString *rest;

- (void)execute_program;
- (void)resultParserPrint:(MyNode *)tree andOrder:(NSString *)order;
@end
