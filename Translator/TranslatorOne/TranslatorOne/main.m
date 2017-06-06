//
//  main.m
//  TranslatorOne
//
//  Created by Ivan on 5/16/17.
//  Copyright © 2017 Ivan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Scanner.h"
#import "Parser.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        
        Scanner *fileScanner = [[Scanner alloc] initWithFileName:@"/Users/ivan/Developer/NTUU-KPI/Translator/TranslatorOne/TranslatorOne/input.txt"];
        
        @try {
            [fileScanner fileScanner];
            //NSLog(@"%@", fileScanner.resultTableArray);
            
            Parser *parser = [[Parser alloc] init];
            parser.listOfTokens = fileScanner.resultTableArray;
            [parser execute_program];
            [parser resultParserPrint:parser.tree andOrder:0];
            
        } @catch (NSException *exception) {
            //NSLog(@"%@", fileScanner.resultTableArray);
            NSLog(@"%@ %@ %@", exception.name, exception.reason, exception.userInfo);
        }
        
    }
    
    return 0;
}
