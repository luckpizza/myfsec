//
//  Encryptor.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Encryptor : NSObject

+ (int) encodeDispacher:(NSString *) filePath password: (NSString *) password options:(NSMutableDictionary *) options;

+ (int) decodeDispacher:(NSString *) path password: (NSString *) password options:(NSMutableDictionary *) options;

+ (int) checkIfFileIsOurs:(NSString*) filePath;

@end
