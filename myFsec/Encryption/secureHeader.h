//
//  secureHeader.h
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include <openssl/md5.h>
#ifndef fsec_secureHeader_h
#define fsec_secureHeader_h



typedef struct secHeader{
    int signature;
    int version;
    unsigned char password[MD5_DIGEST_LENGTH];
    int headerSize;
    long long fileSize;
    int securityLevel;
    int securityType;
    char fileName[255];
}secureHeader;
void printHeader(secureHeader * sHeader);

secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel);
secureHeader * getHeaderFromFile(const char *fileName);

#endif
