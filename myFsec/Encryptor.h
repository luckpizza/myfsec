//
//  Encryptor.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Encryptor : NSObject

+ (int) encodeQuick:(NSString *) path password: (NSString *) password;


+ (int) decodeQuick:(NSString *) path password: (NSString *) password;

+ (int) checkIfFileIsOurs:(NSString*) filePath;

@end
