//
//  encryptUtils.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/22/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_encryptUtils_h
#define fsec_encryptUtils_h

void print_md5_sum(unsigned char* md); 

void encrypt_md5(unsigned char* password,unsigned char * MD5Password);

#endif
