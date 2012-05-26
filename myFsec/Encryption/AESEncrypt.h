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

int AES_encrypt (const char *fileName, const char *password, secureHeader* sHeader);

#endif
