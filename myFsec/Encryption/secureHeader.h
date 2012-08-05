//
//  secureHeader.h
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef fsec_secureHeader_h
#define fsec_secureHeader_h

#include <openssl/sha.h>

#ifdef DEBUG1
#define debugprintHeader(header) printHeader(header)
#else
#define debugprintHeader(header) 
#endif
#define SALT_LENGTH 16

typedef struct secHeader{
    __int32_t signature;
    __int32_t version;
    unsigned char password[SHA256_DIGEST_LENGTH];
    __int32_t headerSize;
    long long fileSize;
    __int32_t securityLevel;
    __int32_t securityType;
    char fileName[255];
    __int32_t extraSize;
    __int32_t saltLength;
    char salt[SALT_LENGTH];
    union u_exra{
        void * extra;
        char don_use[8]; //in order to be the same length in 32 and 64 bits
    }extra;
    
}secureHeader;
void printHeader(secureHeader * sHeader);

/**
 * secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel)
 * Creates an standar secure Header, with some data from the file.
 * returns: a new allocated secureHeader, it is imperative to destroy that header when ever you are done!
 *
 */

secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel);

/**
 * secureHeader * getHeaderFromFile(const char *fileName) {
 * returns: a new allocated secureHeader that's a copy if the header
 *      saved in the file! (REMEMBER TO DESTROY IT WHEN TOU ARE DONE!!)
 *
 */

secureHeader * getHeaderFromFile(const char *fileName);
/**
 *  Destroy Header
 * Frees in a ordered and secured way the secureHeaders.
 * This function should be called when every you are done using a secureHeader and
 * you want to get rid of it!
 */

void destroyHeader(secureHeader * sHeader);

#endif
