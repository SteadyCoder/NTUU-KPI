//
//  Scanner.h
//  TranslatorOne
//
//  Created by Ivan on 5/16/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Scanner : NSObject

@property (nonatomic, strong) NSArray<NSString *> *resultTableArray;

- (void)fileScanner;

- (instancetype)initWithFileName:(NSString *)fileName;


@end
