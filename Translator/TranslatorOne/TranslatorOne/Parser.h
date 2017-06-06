//
//  Parser.h
//  TranslatorOne
//
//  Created by Ivan on 5/31/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MyNode;

@interface Parser : NSObject

@property (nonatomic, strong) NSArray<NSDictionary *> *listOfTokens;
@property (nonatomic, strong) MyNode *tree;
@property (nonatomic, strong) NSString *rest;

- (void)execute_program;
- (void)resultParserPrint:(MyNode *)tree andOrder:(int)order;
@end
