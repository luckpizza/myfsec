//
//  Encryptor.m
//  fsec
//
//  Created by Lucas PIzzagalli on 8/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Encryptor.h"
#import "QuickEncode.h"
#import "EncryptorManager.h"
@implementation Encryptor


+ (int) encodeQuick:(NSString *) filePath password: (NSString *) password
{
    return encodeDispacher([filePath UTF8String], [password UTF8String], 1, SECURITY_TYPE_QUICKENCODE );

    
}


+ (int) decodeQuick:(NSString *) filePath password: (NSString *) password
{
    return decodeDispacher([filePath UTF8String], [password UTF8String]);

}

+ (int) checkIfFileIsOurs:(NSString*) FilePath
{
    return checkIfFileIsOurs([FilePath UTF8String]);
}


@end
