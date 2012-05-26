//
//  secureHeader.cpp
//  fsec
//
//  Created by Lucas PIzzagalli on 9/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#define DEBUG1 

#include <iostream>
#include "secureHeader.h"
#include "Utils.h"
#include <fstream>
#include "QuickEncode.h"
#include "secureHeader.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "encryptUtils.h"
#include "Utils.h"
#include "EncryptorManager.h"
using namespace std;


void printHeader(secureHeader * sHeader)
{
    fprintf(stderr, "signature %d \n version %d \n password", sHeader->signature, sHeader->version);
    print_md5_sum(sHeader->password);
    fprintf(stderr, "\n headerSize %d \n file size: %lld \n file Name: %s \n", sHeader->headerSize, sHeader->fileSize, sHeader->fileName);
    
     
}

secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel){
//   // unsigned char MD5Password[MD5_DIGEST_LENGTH];
    unsigned char SHA256Password[SHA256_DIGEST_LENGTH];
    if(fileName == NULL || *fileName == '\0')
    {
        return NULL;
    }
    //Opening file
    fstream file (fileName, ios::in | ios::out | ios::binary);
    secureHeader *sHeader = (secureHeader *)myMalloc(sizeof(secureHeader));
    memset(sHeader, 0, sizeof(secureHeader));

    //static content
    sHeader->signature = SIGNATURE;
    sHeader->version = VERSION;
    sHeader->securityType = securityType;
    sHeader->securityLevel = securityLevel;
    sHeader->headerSize = sizeof(secureHeader);
    sHeader->extra.extra = NULL;
    sHeader->extraSize = 0;
    //pasword
    hash_sha256((unsigned char*) password, SHA256Password);
    memcpy(sHeader->password, SHA256Password, SHA256_DIGEST_LENGTH);
    
    //getting name of the file
    char *realFileName;
    realFileName = getFileNameFromPath(fileName);
    memcpy(sHeader->fileName, realFileName, strlen(realFileName) + 1);
    
    
    debug("hashed password is \n");
    debugSHA256(SHA256Password);
    
    if (file.is_open() )
    {
        file.seekg(0, ios::end);
        sHeader->fileSize = file.tellg();
        printHeader(sHeader);
        file.close();
        
    } else {
        return NULL;
    }
    file.close();
    return sHeader;
}




secureHeader * getHeaderFromFile(const char *fileName) {
    if(fileName == NULL || *fileName == '\0')
    {
        return NULL;
    }
       
    secureHeader* sHeader = (secureHeader*)myMalloc(sizeof(secureHeader));
    
    fstream file (fileName, ios::in | ios::out | ios::binary);
    
    if (file.is_open() )
    {
        if( checkIfFileIsOurs(&file) != OK)
        {
            debug("file seems not to be ours!");
            return NULL;
        }
        file.read (reinterpret_cast<char*>(&sHeader), sizeof(secureHeader));
    }
    else {
        return NULL;
    }   
    file.close();
    debug("FINISHING GETTING HEADER FROM FILE");
    return sHeader ;
    
}
