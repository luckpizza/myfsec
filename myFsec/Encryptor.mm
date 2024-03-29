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
    printf("keepOldfileValue = %d", [[options objectForKey:KEEP_OLD_FILE] intValue]);
    return encodeDispacher([filePath UTF8String], [password UTF8String], 1, [security intValue] , [[options objectForKey:KEEP_OLD_FILE ] intValue]);

    
}


+ (int) decodeDispacher:(NSString *) filePath password: (NSString *) password options: (NSDictionary *) options
{
    printf("keepOldfileValue = %d", [[options objectForKey:KEEP_OLD_FILE] intValue]);
    return decodeDispacher([filePath UTF8String], [password UTF8String], [[options objectForKey:KEEP_OLD_FILE] intValue]);

}

+ (int) checkIfFileIsOurs:(NSString*) FilePath
{
    return checkIfFileIsOurs([FilePath UTF8String]);
}


@end
