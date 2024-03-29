//
//  encryptUtils.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/22/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_encryptUtils_h
#define fsec_encryptUtils_h

#include "secureHeader.h"

#ifdef DEBUG1
#define debugMD5(md5Hashed) print_md5_sum(md5Hashed)
#else
#define debugMD5(md5Hashed) 
#endif

#ifdef DEBUG1
#define debugSHA256(shaHashed) print_sha256_sum(shaHashed)
#else
#define debugSHA256(md5Hashed) 
#endif

void print_md5_sum(unsigned char* md); 
void print_sha256_sum(unsigned char* md); 
void hash_sha256(unsigned char* password,int lenght, unsigned char * SHA256Password);
void hash_md5(unsigned char* password,unsigned char * MD5Password);
void hash_sha256_salt(unsigned char* password, char* salt,int salt_length, unsigned char * SHA256Password);
char * add_myFsec_extention_string(const char * fileName);
void addMyFsecExtention(const char * fileName);

/**
 *  xorg_bytes:
 * Does the xor byte by byte of the 2 given arrays and stores the result in dst
 * return OK if no error paramenter, ERROR if error;
 */
int xor_bytes(const char * src1, int src1_lenght, const char * src2, int src2_lenght, char * dst);

void recoverOldExtention(const char *fileName, secureHeader * sHeader);

char * recover_old_extention_copy(const char *fileName, secureHeader * sHeader);


/**
 *  This functions fills the byte array with random k chars.
 *  bytes: pointer to the bytes that want to be filled with random data.
 *  k: amount of bytes in the bytes pointer
 *  returns OK if ok, ERROR if any error (ej: k <=0)
 */
int random_k_bytes(char * bytes, int k);

#endif
