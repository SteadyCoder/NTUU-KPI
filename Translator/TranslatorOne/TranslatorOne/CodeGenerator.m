//
//  CodeGenerator.m
//  TranslatorOne
//
//  Created by Ivan on 6/6/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import "CodeGenerator.h"
#import "Scanner.h"
#import "Parser.h"
#import "MyNode.h"

@interface CodeGenerator () {
@public
    NSString *programName;
    NSDictionary *registers;
    NSDictionary *jumps;
    NSDictionary *opposite_jumps;
    NSDictionary *operands;
}

@property (nonatomic, strong) NSString *fileName;

@property (nonatomic, strong) NSMutableDictionary *variablesTable;
@property (nonatomic, strong) NSMutableDictionary *constantTable;
@property (nonatomic, strong) NSMutableArray *labelsTabel;
@property (nonatomic, strong) NSMutableArray *errorLog;

@end

@implementation CodeGenerator

- (instancetype)initWithParser:(Parser *)resultParser andScanner:(Scanner *)resultScanner {
    self = [super init];
    
    if (self) {
        _scanner = resultScanner;
        _parser = resultParser;
        _fileName = @"/Users/ivan/Developer/NTUU-KPI/Translator/TranslatorOne/TranslatorOne/output.txt";
        
        _variablesTable = [NSMutableDictionary dictionary];
        _constantTable = [NSMutableDictionary dictionary];
        _labelsTabel = [NSMutableArray array];
        _errorLog = [NSMutableArray array];
        
        registers = @{@1: @"eax", @2: @"ebx", @3: @"ecx", @4: @"edx"};
        
        jumps = @{
                @"<>": @"jne",
                @"<" : @"jl",
                @">" : @"jg",
                @">=": @"jge",
                @"<=": @"jle",
                @"=" : @"je"
                };
        opposite_jumps = @{
                           @"<>": @"=",
                           @"=": @"<>",
                           @"<": @">=",
                           @">": @"<=",
                           @"<=": @">",
                           @">=": @"<"};
        
        [[NSFileManager defaultManager] createFileAtPath:_fileName contents:nil attributes:nil];
    }
    
    return self;
}

- (void)writeToEndOfFile:(NSString *)stringToWrite {
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForWritingAtPath:self.fileName];
    [fileHandle seekToEndOfFile];
    [fileHandle writeData:[stringToWrite dataUsingEncoding:NSUTF8StringEncoding]];
}

// Generate the start label for the text
- (void)generateProgramTextStart {
    [self writeToEndOfFile:[NSString stringWithFormat:@"%@:\n", programName]];
}

- (void)generateComparison:(MyNode *)node {
    NSString *firstOperand = node.children[0].children[0].data;
    NSDictionary *dictionaryFirst = [NSJSONSerialization JSONObjectWithData:[firstOperand dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
    NSString *secondOperand = node.children[2].children[0].data;
    NSDictionary *dictionarySecond = [NSJSONSerialization JSONObjectWithData:[secondOperand dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
    
    [self writeToEndOfFile:[NSString stringWithFormat:@"\tcmp %@ %@\n", dictionaryFirst[kTokenKeyNameLexem], dictionarySecond[kTokenKeyNameLexem]]];
    NSString *compareOperator = node.children[1].children[0].data;
    if ([jumps.allKeys containsObject:compareOperator]) {
        NSString *label = [NSString stringWithFormat:@"label%ld", self.labelsTabel.count];
        [self.labelsTabel addObject:label];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t%@ %@\n", jumps[opposite_jumps[compareOperator]], label]];
    }
}

- (void)generateAssign:(MyNode *)node {
    NSLog(@"generate");
    MyNode *childNode = node.children[1];
    NSDictionary *resultOperand = [NSJSONSerialization JSONObjectWithData:[node.children[0].children[0].data dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
    
    NSString *firstOperand;
    NSString *secondOperand;
    NSDictionary *firstDictionary;
    NSDictionary *secondDictionary;
    
    if ([childNode.children[0].rule isEqualToString:kKeyVariableIdentifier]) {
        firstDictionary = [NSJSONSerialization JSONObjectWithData:[childNode.children[0].children[0].data dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
        firstOperand = firstDictionary[kTokenKeyNameLexem];
    } else {
        firstOperand = childNode.children[0].data;
    }
    
    if ([childNode.children[2].rule isEqualToString:kKeyVariableIdentifier]) {
        secondDictionary = [NSJSONSerialization JSONObjectWithData:[childNode.children[2].children[0].data dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
        secondOperand = secondDictionary[kTokenKeyNameLexem];
    } else {
        secondOperand = childNode.children[2].data;
    }
    
    if ([childNode.children[1].children[0].data isEqualToString:@"-"]) {
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV EAX, %@\n", firstOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tSUB EAX, %@\n", secondOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV %@, EAX\n", resultOperand[kTokenKeyNameLexem]]];
    } else if ([childNode.children[1].children[0].data isEqualToString:@"+"]) {
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV EAX, %@\n", firstOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tADD EAX, %@\n", secondOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV %@, EAX\n", resultOperand[kTokenKeyNameLexem]]];
    } else if ([childNode.children[1].children[0].data isEqualToString:@"*"]) {
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV EAX, %@\n", firstOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMUL EAX, %@\n", secondOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV %@, EAX\n", resultOperand[kTokenKeyNameLexem]]];
    } else if ([childNode.children[1].children[0].data isEqualToString:@"/"]) {
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV EAX, %@\n", firstOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tDIV EAX, %@\n", secondOperand]];
        [self writeToEndOfFile:[NSString stringWithFormat:@"\t\tMOV %@, EAX\n", resultOperand[kTokenKeyNameLexem]]];
    }
    
}

// Generate a segment for variables
- (void)generateBssVar:(MyNode *)node {
    NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:[node.children[0].children[0].data dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil];
    if ([self.variablesTable.allKeys containsObject:dictionary[kTokenKeyNameLexem]] || [dictionary[kTokenKeyNameLexem] isEqualToString:programName]) {
        [self.errorLog addObject:dictionary[kTokenKeyNameLexem]];
    } else {
        [self.variablesTable setValue:dictionary[kTokenKeyNameLexem] forKey:[NSString stringWithFormat:@"%ld", self.variablesTable.count]];
        // Write to file
        if ([node.children[2].data isEqualToString:@"INTEGER"]) {
            [self writeToEndOfFile:[NSString stringWithFormat: @"\t%@\tDD\t0\n", dictionary[kTokenKeyNameLexem]]];
        } else {
            [self writeToEndOfFile:[NSString stringWithFormat: @"\t%@\tDQ\t0\n", dictionary[kTokenKeyNameLexem]]];
        }
        
    }
}

- (BOOL)treeMaker:(MyNode *)node {
    BOOL result = NO;
    
    if ([node.rule isEqualToString:kKeyProcedureIdentifier]) {
        NSData *data = [node.children[0].data dataUsingEncoding:NSUTF8StringEncoding];
        NSDictionary *dictionary = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
        NSString *program_start = [NSString stringWithFormat:@"section .text\n\tglobal %@\n", dictionary[kTokenKeyNameLexem]];
        programName = dictionary[kTokenKeyNameLexem];
        [self writeToEndOfFile:program_start];
        result = YES;
    } else if ([node.rule isEqualToString:kKeyVariableDeclaration]) {
        [self writeToEndOfFile:@"segment .bss\n"];
    } else if ([node.rule isEqualToString:kKeyDeclaration]) {
        [self generateBssVar:node];
        result = YES;
    } else if ([node.rule isEqualToString:kKeyWord] && [node.data containsString:@"BEGIN"]) {
        [self generateProgramTextStart];
    } else if ([node.rule isEqualToString:kKeyWord] && [node.data containsString:@"END"]) {
        
    } else if ([node.rule isEqualToString:kKeyStatement]) {
        NSLog(@"statement start");
        if ([node.children[0].data isEqualToString:@"IF"]) {
            [self generateComparison:node.children[1]];
            
            [self generateCode:node.children[3]];
            
            result = YES;
        } else if ([node.children[0].rule isEqualToString:kKeyAssignOperation]) {
            NSLog(@"assign operation");
            [self generateAssign:node.children[0]];
            result = YES;
        }
    } else if ([node.rule isEqualToString:kKeyConditionalExpression]) {
        
    }
    
    return result;
}

- (void)generateCode:(MyNode *)node {
    if ([self treeMaker:node]) {
        return;
    }
    for (MyNode *nd in node.children) {
        [self generateCode:nd];
    }
    
}

@end
