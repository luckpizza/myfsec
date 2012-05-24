//
//  File.cpp
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
//#define DEBUG
#define DEBUG1 
#include <iostream>
#include <fstream>
#include "QuickEncode.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "encryptUtils.h"
#include "Utils.h"
#include "EncryptorManager.h"


unsigned char SHA256Password[SHA256_DIGEST_LENGTH];
int initDecoderHeader(const char *fileName, const char *password, secureHeader * sHeader);
int checkIfFileIsOurs(std::fstream* file );

using namespace std;

//ifstream::pos_type size;
/**
 *
 * encode a file with the given password
 * @param fileName the file name that we want to encrypt
 * @param password the password that will be used to encrypt the file
 * @return ENCODED if ok, error otherwise
 */


int encodeQuick (const char *fileName, const char *password, secureHeader* sHeader) {
    if(fileName == NULL || *fileName == '\0' || sHeader == NULL)
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }


    fstream file (fileName, ios::in | ios::out | ios::binary);
    
    long long sizeReaded;
    char buffer[sizeof(secureHeader)];
    memset(buffer, 0, sizeof(secureHeader));

    if (file.is_open() )
    {
        file.seekg (0);
        if(!file.read (buffer, sizeof(secureHeader)))
        {
            debug( "File is smaller than Header");//sizeof(sHeader));
            file.clear();
        }
        sizeReaded =file.gcount();
        //Writing first sizeof(secureHeader) bytes to the end of the file
        file.seekp(0,ios::end);
        file.write(reinterpret_cast<char*>(buffer), sizeReaded);
        //Writting header to file
        file.seekp(0,ios::beg);
        file.write(reinterpret_cast<char*>(sHeader), sizeof(secureHeader) );
        file.flush();
        file.close();
            
    } else {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    addMyFsecExtention(fileName);
    /*
        else cout << "Unable to open file";
        printf("file name was: %s and password: %s", fileName, password);
      */
    debug("FINISHING ENCRYPT");
    return ENCODED;
} 


//int decodeChecks
 int initDecoderHeader(const char *fileName, const char *password, secureHeader * sHeader){
    //Make sure that the file that want to be dencrypted has the correct extention. 
    char * tempName = (char *)myMalloc(strlen(fileName) + 1);
     int error;
     strcpy(tempName, fileName);
    char * extention = strrchr(tempName, '.');
    myFree(tempName);
    if(extention == NULL || strcmp(extention, FSEC_EXTENTION) != 0)
    {
        debug( "File doesn't look like one of us!");
        return  ERROR_NOT_SUPPORTED;
    }
    fstream file (fileName, ios::in | ios::out | ios::binary);
    
    if (!file.is_open() ){
        debug("Unable to open the file!");
        return  ERROR_FILE_DOES_NOT_EXIST;
    }
    
    
    if((error = checkIfFileIsOurs(&file)) != OK)
    {
        debug("file seems not to be ours!");
        return error;
    }
    file.read (reinterpret_cast<char*>(sHeader), sizeof(secureHeader));
    hash_sha256((unsigned char*) password, SHA256Password);
    debug("hashed password is \n");
    debugSHA256(SHA256Password);
    debug("password in the header is: \n");
#ifdef DEBUG
    print_md5_sum(sHeader->password);
    debug("HEADER READ IS: \n");
    printHeader(sHeader);
    
#endif
    
    if(memcmp(sHeader->password, SHA256Password, SHA256_DIGEST_LENGTH) != 0)
    {
        debug( "wrong password!");
        return  ERROR_WRONG_PASSWORD;
    }
     file.close();
     return DECODED;
     
}




int decodeQuick(const char *fileName, const char *password) {
    if(fileName == NULL || *fileName == '\0')
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    int msgCode = DECODED;
    secureHeader sHeader;
    long long fileSizeMoved;
    char buffer[sizeof(sHeader)];
   
    if((msgCode = initDecoderHeader(fileName, password, &sHeader))!= DECODED){
        return msgCode;
    }
    fstream file (fileName, ios::in | ios::out | ios::binary);
    if(!file.is_open()){
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    fileSizeMoved = sizeof(secureHeader);
    if(sHeader.fileSize <= sizeof(secureHeader))                        //if the file was too small go back that amount
        fileSizeMoved = sHeader.fileSize;
    file.seekg (-fileSizeMoved, ios::end);
    if(!file.read (reinterpret_cast<char*>(buffer),fileSizeMoved)){    //Read the bytes moved to the end of the file
        cout << "error"; 
        return  -1;
    }
    //Restoring the bytes moved to the end, again in their original possition
    file.seekp (0, ios::beg);
    file.write(reinterpret_cast<char*>(buffer), fileSizeMoved);
    file.flush();
    file.close();
    //Truncating the file to its oroginal size
    truncate(fileName, sHeader.fileSize);
    debug( "the complete file content is in memory");
    debug("decrypting: %s and password: %s", fileName, password);
    recoverOldExtention(fileName, &sHeader);    
    
    debug("FINISHING DECRYPT");
    return msgCode ;
    
}

