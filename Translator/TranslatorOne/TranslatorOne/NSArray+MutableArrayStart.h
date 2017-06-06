//
//  NSMutableArray+MutableArrayStart.h
//  TranslatorOne
//
//  Created by Ivan on 6/3/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (MutableArrayStart)
- (NSMutableArray *)mutableArrayFromTheStartPoint:(NSUInteger)start;
@end

@interface NSArray (ArrayStart)
- (NSMutableArray *)mutableArrayFromTheStartPoint:(NSUInteger)start;
@end
