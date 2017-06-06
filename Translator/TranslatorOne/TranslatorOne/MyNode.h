//
//  MyNode.h
//  TranslatorOne
//
//  Created by Ivan on 5/31/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyNode : NSObject

@property (nonatomic, strong) NSString *data;
@property (nonatomic, strong) NSString *rule;
@property (nonatomic, strong) MyNode *parent;
@property (nonatomic, strong) NSArray<MyNode *> *children;

- (instancetype)initWithData:(NSString *)data aRule:(NSString *)rule aParent:(MyNode *)parent;
+ (instancetype)nodeWithData:(NSString *)data rule:(NSString *)aRule parent:(MyNode *)aParent;

- (void)addChild:(MyNode *)child;

+ (instancetype)errorNode;
+ (instancetype)errorNodeWithData:(NSDictionary *)data;
@end
