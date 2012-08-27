//
//  File.cpp
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
//#define DEBUG
#define DEBUG1 1

#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/sha.h>

#include "QuickEncode.h"
#include "Utils.h"
#include "EncryptorManager.h"

extern double _g_total_to_do;
extern double _g_amount_done;

int initDecoderHeader(const char *fileName, const char *password, secureHeader * sHeader);
int checkIfFileIsOurs(std::fstream* file );

using namespace std;

/**
 * @function int encodeQuick (const char *fileName, const char *password, secureHeader* sHeader) 
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
        _g_total_to_do = sHeader->fileSize;

        file.seekg (0);
        int file_too_short = 0;
        if((file_too_short = (sizeReaded = file.readsome (buffer, sizeof(secureHeader))) < sizeof(secureHeader)))
        {
            debug( "File is smaller than Header");//sizeof(sHeader));
        }
        //Writing first sizeof(secureHeader) bytes to the end of the file
        if( file_too_short)
        {
            file.seekg(sizeof(secureHeader));
        }else
        {
            file.seekp(0,ios::end);   
        }
        file.write(reinterpret_cast<char*>(buffer), sizeReaded);
        //Writting header to file
        file.seekp(0,ios::beg);
        file.write(reinterpret_cast<char*>(sHeader), sizeof(secureHeader) );
        file.flush();
        file.close();
        _g_amount_done = sHeader->fileSize;

    } else {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    /*
        else cout << "Unable to open file";
        printf("file name was: %s and password: %s", fileName, password);
      */
    debug("FINISHING ENCRYPT");
    return ENCODED;
} 

/**
 * @function int decodeQuick(const char *fileName, const char *password, secureHeader * sHeader)
 * Decodes a file encrypted using the QuickEncode
 */
int decodeQuick(const char *fileName, const char *password, secureHeader * sHeader) {
    if(fileName == NULL || *fileName == '\0' || sHeader == NULL)
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    int msgCode = DECODED;
    long long fileSizeMoved;
    char buffer[sizeof(secureHeader)];
    _g_total_to_do = sHeader->fileSize;
    fstream file (fileName, ios::in | ios::out | ios::binary);
    if(!file.is_open()){
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    fileSizeMoved = sizeof(secureHeader);
    if(sHeader->fileSize <= sizeof(secureHeader))                        //if the file was too small go back that amount
        fileSizeMoved = sHeader->fileSize;
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
    _g_amount_done = sHeader->fileSize;

    //Truncating the file to its oroginal size
    truncate(fileName, sHeader->fileSize);
    debug( "the complete file content is in memory");
    debug("decrypting: %s and password: %s", fileName, password);
    recoverOldExtention(fileName, sHeader);    
    
    debug("FINISHING DECRYPT");
    return msgCode ;
    
}

