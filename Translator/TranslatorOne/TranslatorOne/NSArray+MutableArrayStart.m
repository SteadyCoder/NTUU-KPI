//
//  NSMutableArray+MutableArrayStart.m
//  TranslatorOne
//
//  Created by Ivan on 6/3/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import "NSMutableArray+MutableArrayStart.h"

@implementation NSMutableArray (MutableArrayStart)

- (NSMutableArray *)mutableArrayFromTheStartPoint:(NSUInteger)start {
    return [[NSMutableArray alloc] initWithArray:[self subarrayWithRange:NSMakeRange(start, self.count - 1)]];
}
@end
