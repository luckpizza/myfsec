//
//  secureHeader.cpp
//  fsec
//
//  Created by Lucas PIzzagalli on 9/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#define DEBUG1 1

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/sha.h>

#include "QuickEncode.h"
#include "secureHeader.h"
#include "encryptUtils.h"
#include "Utils.h"
#include "EncryptorManager.h"

using namespace std;


void printHeader(secureHeader * sHeader)
{
    fprintf(stderr, "signature %d \n version %d \n password", sHeader->signature, sHeader->version);
   // print_md5_sum(sHeader->password);
    fprintf(stderr, "\n headerSize %d \n file size: %lld \n file Name: %s \n", sHeader->headerSize, sHeader->fileSize, sHeader->fileName);
    
     
}

/**
 * secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel)
 * Creates an standar secure Header, with some data from the file.
 * returns: a new allocated secureHeader, it is imperative to destroy that header when ever you are done!
 *  
 */
secureHeader * createHeaderForFile(const char *fileName,const  char * password, int securityType, int securityLevel){
    unsigned char SHA256Password[SHA256_DIGEST_LENGTH];
    char salt[SALT_LENGTH];
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
    //salt
    sHeader->saltLength = SALT_LENGTH;
    random_k_bytes(salt, SALT_LENGTH);
    memcpy(sHeader->salt, salt, SALT_LENGTH);
    //pasword
    hash_sha256_salt((unsigned char*) password,sHeader->salt, sHeader->saltLength, SHA256Password);
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
    printHeader(sHeader);
    file.close();
    return sHeader;
}


/**
 * secureHeader * getHeaderFromFile(const char *fileName) {
 * returns: a new allocated secureHeader that's a copy if the header 
 *      saved in the file! (REMEMBER TO DESTROY IT WHEN TOU ARE DONE!!)
 *
 */
secureHeader * getHeaderFromFile(const char *fileName) {
    int status = OK;
    if(fileName == NULL || *fileName == '\0')
    {
        return NULL;
    }
       
    secureHeader* sHeader = (secureHeader*)myMalloc(sizeof(secureHeader));
    
    fstream file (fileName, ios::in | ios::out | ios::binary);
    
    if (file.is_open() )
    {
        if( (status = checkIfFileIsOurs(&file)) == ERROR_FILE_DOES_NOT_EXIST || status == ERROR_NOT_SUPPORTED)
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
    printHeader(sHeader);
    debug("FINISHING GETTING HEADER FROM FILE");
    return sHeader ;
    
}

/**
 *  Destroy Header
 * Frees in a ordered and secured way the secureHeaders.
 * This function should be called when every you are done using a secureHeader and 
 * you want to get rid of it!
 */
void destroyHeader(secureHeader * sHeader)
{
    if(sHeader->extra.extra != NULL){
        myFree(sHeader->extra.extra);
    }
    myFree(sHeader);
}