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
#import "EncryptionOptions.h"

@implementation Encryptor


+ (int) encodeDispacher:(NSString *) filePath password: (NSString *) password options: (NSDictionary *) options 
{
    NSNumber * security = (NSNumber*)[options objectForKey:OPTION_SECURITY];
    return encodeDispacher([filePath UTF8String], [password UTF8String], 1, [security intValue] , 0);

    
}


+ (int) decodeDispacher:(NSString *) filePath password: (NSString *) password options: (NSDictionary *) options
{
    
    return decodeDispacher([filePath UTF8String], [password UTF8String], 0);

}

+ (int) checkIfFileIsOurs:(NSString*) FilePath
{
    return checkIfFileIsOurs([FilePath UTF8String]);
}


@end
