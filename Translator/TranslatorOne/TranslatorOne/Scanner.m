//
//  Scanner.m
//  TranslatorOne
//
//  Created by Ivan on 5/16/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import "Scanner.h"

const NSString * kTokenKeyNameId = @"id";
const NSString * kTokenKeyNameRow = @"row";
const NSString * kTokenKeyNameColumn = @"column";
const NSString * kTokenKeyNameLexem = @"word";

@interface NSString (ASCIIValue)

- (NSUInteger)asciiValue;

@end

@implementation NSString (ASCIIValue)

- (NSUInteger)asciiValue {
    return (int)[self characterAtIndex:0];
}

@end

@interface Scanner () {
    NSDictionary<NSString*, NSNumber*> *delimiters;
    NSDictionary<NSString*, NSNumber*> *keywords;
}

@property (nonatomic, strong) NSString *fileName;
@property (nonatomic, strong) NSMutableArray<NSNumber*> *attributeArray;
@property (nonatomic, strong) NSMutableDictionary *tableID;
@property (nonatomic, strong) NSMutableDictionary *tableConstants;

@end

@implementation Scanner

- (instancetype)init {
    self = [super init];
    
    delimiters = @{@";": @200,
                   @".": @201,
                   @":": @202,
                   @"=": @203,
                   @">": @204,
                   @"<": @205,
                   @"+": @206,
                   @"-": @207,
                   @"*": @208,
                   @"/": @209};
    
    keywords = @{@"PROGRAM": @100,
                 @"BEGIN": @101,
                 @"END": @102,
                 @"VAR": @103,
                 @"INTEGER": @104,
                 @"FLOAT": @105,
                 @"WHILE": @106,
                 @"DO": @107,
                 @"ENDWHILE": @108,
                 @"<=": @109,
                 @"<>": @110,
                 @">=": @111,
                 
                 @"IF": @112,
                 @"THEN": @113,
                 @"ELSE": @114,
                 @":=": @115};
    
    
    if (self) {
        _attributeArray = [NSMutableArray arrayWithCapacity:128];
        _tableID = [NSMutableDictionary new];
        _tableConstants = [NSMutableDictionary new];
        for (int i = 0; i < 128; i++) {
            _attributeArray[i] = @6;
        }
    }
    
    return self;
}

- (instancetype)initWithFileName:(NSString *)fileName {
    self = [self init];
    
    if (self) {
        for (int i = 0; i < 128; i++) {
            switch (i) {
                case 0 ... 32:
                    _attributeArray[i] = @0;
                    break;
                case 48 ... 58:
                    _attributeArray[i] = @1;
                    break;
                case 65 ... 90:
                    _attributeArray[i] = @2;
                    break;
                case 97 ... 122:
                    _attributeArray[i] = @2;
                    break;
                default:
                    break;
            }
        }
        
        _attributeArray[40] = @5;
        _attributeArray[41] = @6;
        
        _attributeArray[42] = @3;
        _attributeArray[43] = @3;
        _attributeArray[45] = @3;
        _attributeArray[47] = @3;
        _attributeArray[58] = @3;
        _attributeArray[59] = @3;
        _attributeArray[46] = @3;
        _attributeArray[61] = @3;
        
        _attributeArray[60] = @4;
        _attributeArray[62] = @4;
        
        _fileName = fileName;
    }
    
    return self;
}

- (NSNumber *)addToTableID:(NSString *)aToken {
    if ([keywords.allKeys containsObject:aToken]) {
        return keywords[aToken];
    } else if ([delimiters.allKeys containsObject:aToken]) {
        return delimiters[aToken];
    } else if ([self.tableID.allKeys containsObject:aToken]) {
        return self.tableID[aToken];
    } else {
        self.tableID[aToken] = @(self.tableID.count + 1000);
        return self.tableID[aToken];
    }
}

- (NSNumber *)addToContastantTable:(NSString *)aToken {
    if ([self.tableConstants.allKeys containsObject:aToken]) {
        return self.tableConstants[aToken];
    } else {
        self.tableConstants[aToken] = @(self.tableConstants.count + 300);
        return self.tableConstants[aToken];
    }
}

- (void)fileScanner {
    NSFileHandle *file = [NSFileHandle fileHandleForReadingAtPath:self.fileName];
    NSData *dataRead = [file readDataOfLength:1];
    
    NSMutableArray<NSDictionary *> *resultArray = [NSMutableArray array];
    NSUInteger row = 1;
    NSUInteger column = 0;
    
    NSString *string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
    
    if ([dataRead.className isEqualToString:@"_NSZeroData"]) {
        NSLog(@"Empty file");
    }
    
    while (![dataRead.className isEqualToString:@"_NSZeroData"]) {
        
        NSMutableString *wordBuffer = [NSMutableString string];
        NSUInteger index = string.asciiValue;
        
        if ([self.attributeArray[index] isEqual: @0]) {
            while (![dataRead.className isEqualToString:@"_NSZeroData"] && [self.attributeArray[string.asciiValue] isEqual:@0]) {
                if (string.asciiValue == 10) {
                    row += 1;
                    column = 0;
                } else {
                    column += 1;
                }
                dataRead = [file readDataOfLength:1];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            }
        } else if ([self.attributeArray[index] isEqual:@1]) {
            column += 1;
            while (![(dataRead = [file readDataOfLength:1]).className isEqualToString:@"_NSZeroData"] && [self.attributeArray[string.asciiValue] isEqual:@1]) {
                [wordBuffer appendString:string];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            }
            [resultArray addObject:@{kTokenKeyNameId: [self addToContastantTable:wordBuffer], kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: wordBuffer}];
            
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            column += wordBuffer.length - 1;
        } else if ([self.attributeArray[index] isEqual:@2]) {
            column += 1;
            while (![dataRead.className isEqualToString:@"_NSZeroData"] && ([self.attributeArray[string.asciiValue] isEqual:@2] || [self.attributeArray[string.asciiValue] isEqual:@1])) {
                [wordBuffer appendString:string.uppercaseString];
                dataRead = [file readDataOfLength:1];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            }

            [resultArray addObject:@{kTokenKeyNameId: [self addToTableID:wordBuffer], kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: wordBuffer}];
            column += wordBuffer.length - 1;
        } else if ([self.attributeArray[index] isEqual:@3]) {
            [wordBuffer appendString:string];
            
            dataRead = [file readDataOfLength:1];
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            [wordBuffer appendString:string];
            if ([keywords.allKeys containsObject:wordBuffer]) {
                column += 2;
                [resultArray addObject:@{kTokenKeyNameId: keywords[wordBuffer], kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column),
                                         kTokenKeyNameLexem: wordBuffer}];
                dataRead = [file readDataOfLength:1];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            } else {
                column += 1;
                NSString *firstCharacter = [NSString stringWithFormat:@"%c", [wordBuffer characterAtIndex:0]];
                [resultArray addObject:@{kTokenKeyNameId: delimiters[firstCharacter], kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: firstCharacter}];
                dataRead = [file readDataOfLength:1];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            }
            
        } else if ([self.attributeArray[index] isEqual:@4]) {
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            [wordBuffer appendString:string];
            
            dataRead = [file readDataOfLength:1];
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            [wordBuffer appendString:string];
            if ([keywords.allKeys containsObject:wordBuffer]) {
                column += 2;
                [resultArray addObject:@{kTokenKeyNameId: keywords[wordBuffer], kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: wordBuffer}];
                dataRead = [file readDataOfLength:1];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            } else {
                column += 1;
                NSString *firstCharacter = [NSString stringWithFormat:@"%c", [wordBuffer characterAtIndex:0]];
                [resultArray addObject:@{kTokenKeyNameId: delimiters[firstCharacter], kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: firstCharacter}];
            }
        } else if ([self.attributeArray[index] isEqual:@5]) {
            BOOL flag = NO;
            dataRead = [file readDataOfLength:1];
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            if ([string isEqualToString:@"*"]) {
                column += 2;
                while (![(dataRead = [file readDataOfLength:1]).className isEqualToString:@"_NSZeroData"]) {
                    flag = YES;
                    string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
                    if ([string isEqualToString:@"\n"]) {
                        row += 1;
                        column = 0;
                    } else if ([string isEqualToString:@"*"]) {
                        dataRead = [file readDataOfLength:1];
                        string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
                        if ([string isEqualToString:@")"]) {
                            column += 2;
                            flag = NO;
                            break;
                        }
                        column += 1;
                    }
                }
                if (flag) {
                    self.resultTableArray = resultArray;
                    @throw [NSException exceptionWithName:@"ERROR! Expected '*'" reason:@"End of file met" userInfo:@{@"Tint": @"Perhaps forgot to close comments", @"Error line": [NSString stringWithFormat:@"line %ld column %ld", row - 3, column]}];
                }
                dataRead = [file readDataOfLength:1];
                string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            } else {
                column += 1;
                [resultArray addObject:@{kTokenKeyNameId: @"ERROR", kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: @"("}];
            }
        } else if ([self.attributeArray[index] isEqualToNumber:@6]) {
            column += 1;
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
            [resultArray addObject:@{kTokenKeyNameId: @"ERROR", kTokenKeyNameRow: @(row), kTokenKeyNameColumn: @(column), kTokenKeyNameLexem: string}];
            dataRead = [file readDataOfLength:1];
            string = [[NSString alloc] initWithData:dataRead encoding:NSUTF8StringEncoding];
        }
    }
    [file closeFile];
    self.resultTableArray = resultArray;
}

- (NSUInteger)ascii:(NSString *)string {
    if (string)
        return (int)[string characterAtIndex:0];
    return 0;
}


@end
