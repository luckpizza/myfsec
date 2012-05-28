//
//  AESEncrypt.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef myFsec_AESEncrypt_h
#define myFsec_AESEncrypt_h
#import "secureHeader.h"
#define SECURITY_TYPE_AES256 2
int AES_encrypt (const char *fileName, const char *password, secureHeader* sHeader);
int AES_decrypt (const char *fileName, const char *password, secureHeader* sHeader);
#endif
