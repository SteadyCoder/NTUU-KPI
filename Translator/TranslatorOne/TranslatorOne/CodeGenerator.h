//
//  CodeGenerator.h
//  TranslatorOne
//
//  Created by Ivan on 6/6/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Parser, Scanner, MyNode;

@interface CodeGenerator : NSObject

@property (nonatomic, strong) Parser *parser;
@property (nonatomic, strong) Scanner *scanner;

- (instancetype)initWithParser:(Parser *)resultParser andScanner:(Scanner *)resultScanner;

- (void)generateCode:(MyNode *)node;

@end
