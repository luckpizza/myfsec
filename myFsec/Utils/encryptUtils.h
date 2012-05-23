//
//  encryptUtils.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/22/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_encryptUtils_h
#define fsec_encryptUtils_h

#ifdef DEBUG1
#define debugMD5(md5Hashed) print_md5_sum(md5Hashed)
#else
#define debugMD5(md5Hashed) 
#endif
void print_md5_sum(unsigned char* md); 

void encrypt_md5(unsigned char* password,unsigned char * MD5Password);

#endif
