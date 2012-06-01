//
//  secureHeader.h
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include <openssl/md5.h>
#include <openssl/sha.h>
#ifndef fsec_secureHeader_h
#define fsec_secureHeader_h
#ifdef DEBUG1
#define debugprintHeader(header) printHeader(header)
#else
#define debugprintHeader(header) 
#endif

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
    union u_exra{
        void * extra;
        char don_use[8]; //in order to be the same length in 32 and 64 bits
    }extra;
    
}secureHeader;
void printHeader(secureHeader * sHeader);

secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel);
secureHeader * getHeaderFromFile(const char *fileName);

#endif
