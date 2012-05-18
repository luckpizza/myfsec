//
//  Encryptor.m
//  fsec
//
//  Created by Lucas PIzzagalli on 8/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Encryptor.h"
#import "QuickEncode.h"
@implementation Encryptor

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (int) encodeQuick:(NSString *) filePath password: (NSString *) password
{
    return encodeQuick([filePath UTF8String], [password UTF8String]);

    
}


- (int) decodeQuick:(NSString *) filePath password: (NSString *) password
{
    return decodeQuick([filePath UTF8String], [password UTF8String]);

}

- (int) checkIfFileIsOurs:(NSString*) FilePath
{
    return checkIfFileIsOurs([FilePath UTF8String]);
}


@end
