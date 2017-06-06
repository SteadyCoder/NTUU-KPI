//
//  Scanner.h
//  TranslatorOne
//
//  Created by Ivan on 5/16/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

extern const NSString * kTokenKeyNameId;
extern const NSString * kTokenKeyNameRow;
extern const NSString * kTokenKeyNameColumn;
extern const NSString * kTokenKeyNameLexem;

@interface Scanner : NSObject

@property (nonatomic, strong) NSArray<NSDictionary *> *resultTableArray;

- (void)fileScanner;

- (instancetype)initWithFileName:(NSString *)fileName;


@end
