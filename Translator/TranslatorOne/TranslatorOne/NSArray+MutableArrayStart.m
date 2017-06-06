//
//  NSMutableArray+MutableArrayStart.m
//  TranslatorOne
//
//  Created by Ivan on 6/3/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import "NSArray+MutableArrayStart.h"


@implementation NSMutableArray (MutableArrayStart)

- (NSMutableArray *)mutableArrayFromTheStartPoint:(NSUInteger)start {
    return [[NSMutableArray alloc] initWithArray:[self subarrayWithRange:NSMakeRange(start, self.count - start)]];
}
@end

@implementation NSArray (ArrayStart)

- (NSMutableArray *)mutableArrayFromTheStartPoint:(NSUInteger)start {
    return [[NSMutableArray alloc] initWithArray:[self subarrayWithRange:NSMakeRange(start, self.count - start)]];
}
@end
