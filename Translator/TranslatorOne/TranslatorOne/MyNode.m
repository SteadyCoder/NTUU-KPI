//
//  MyNode.m
//  TranslatorOne
//
//  Created by Ivan on 5/31/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import "MyNode.h"
#import "Scanner.h"

@interface MyNode ()

@property(nonatomic, strong) NSMutableArray<MyNode *> *mutableChildren;

@end

@implementation MyNode

- (instancetype)initWithData:(NSString *)data aRule:(NSString *)rule aParent:(MyNode *)parent {
    self = [super init];
    if (self) {
        _data = data;
        _rule = rule;
        _parent = parent;
    }
    return self;
}

+ (instancetype)nodeWithData:(NSString *)data rule:(NSString *)aRule parent:(MyNode *)aParent {
    return [[MyNode alloc] initWithData:data aRule:aRule aParent:aParent];
}

+ (instancetype)errorNode {
    return [[MyNode alloc] initWithData:nil aRule:@"ERROR" aParent:nil];
}

+ (instancetype)errorNodeWithData:(NSDictionary *)data {
    NSString *stringData = [NSString stringWithFormat:@"row %ld; column %@", [data[kTokenKeyNameRow] integerValue] + 1, data[kTokenKeyNameColumn]];
    return [[MyNode alloc] initWithData:stringData aRule:@"ERROR" aParent:nil];
}

- (void)addChild:(MyNode *)child {
    if (!self.mutableChildren)
        _mutableChildren = [NSMutableArray new];
    if (child)
        [_mutableChildren addObject:child];
}

- (NSArray<MyNode *> *)children {
    return self.mutableChildren;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"Data: %@, rule: %@, parent %@", self.data, self.rule, self.parent.rule];
}

@end
