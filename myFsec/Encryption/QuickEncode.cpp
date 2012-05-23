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
#include "encryptUtils.h"
#include "Utils.h"
#include "EncryptorManager.h"



unsigned char MD5Password[MD5_DIGEST_LENGTH];

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
        file.seekp(0,ios::end);
        file.write(reinterpret_cast<char*>(buffer), sizeReaded);
        file.seekp(0,ios::beg);
        file.write(reinterpret_cast<char*>(sHeader), sizeof(secureHeader) );
        file.flush();
        file.close();
            
    } else {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    char * temp = (char *)myMalloc(strlen(fileName) + strlen(FSEC_EXTENTION) + 1);
    strcpy(temp, fileName);
    strcat(temp, FSEC_EXTENTION);
    rename(fileName, temp);
    myFree(temp);
    myFree(sHeader);
    /*
        else cout << "Unable to open file";
        printf("file name was: %s and password: %s", fileName, password);
      */
    debug("FINISHING ENCRYPT");
    return ENCODED;
} 




int decodeQuick(const char *fileName, const char *password) {
    if(fileName == NULL || *fileName == '\0')
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    int msgCode = DECODED;
    
    //vars that will be used to calculate the new path and filename
    char * newFilePath = getOnlyPath(fileName);
    char * newFilePathAndName;
    //Make sure that the file that want to be dencrypted has the correct extation. 
    char * tempName = (char *)myMalloc(strlen(fileName) + 1);
    strcpy(tempName, fileName);
    char * extention = strrchr(tempName, '.');
    if(extention == NULL || strcmp(extention, FSEC_EXTENTION) != 0)
    {
        cout << "File doesn't look like one of us!";
        free(tempName);
        return ERROR_NOT_SUPPORTED;
    }
    // Preparing the new file name (without the extation)
    *extention = '\0';
    fstream file (fileName, ios::in | ios::out | ios::binary);
    secureHeader sHeader;
    long long fileSizeMoved;
    char buffer[sizeof(sHeader)];
    
    if (file.is_open() )
    {
        //            file.seekg (0, ios::beg);
        //            //Checking if file is supported 
        //            if(!file.read (reinterpret_cast<char*>(&sHeader), sizeof(sHeader)))
        //            {
        //                cout << "File doesnt seem to be encrypted";
        //                return ERROR_NOT_SUPPORTED;
        //            }
        //            if(sHeader.signature != SIGNATURE || sHeader.version != VERSION || sHeader.headerSize != sizeof(sHeader)  )
        //            {
        //                cout << "File does not seems to be encrypted by us, sorry";
        //                return ERROR_NOT_SUPPORTED;
        //            }
        
        if((msgCode = checkIfFileIsOurs(&file)) != OK)
        {
            debug("file seems not to be ours!");
            return msgCode;
        }
        else
           {
               msgCode = DECODED;
               file.read (reinterpret_cast<char*>(&sHeader), sizeof(sHeader));
               encrypt_md5((unsigned char*) password, MD5Password);
               debug("hashed password is \n");
#ifdef DEBUG
               print_md5_sum(MD5Password);
#endif
               debug("password in the header is: \n");
#ifdef DEBUG
               print_md5_sum(sHeader.password);
               debug("HEADER READ IS: \n");
                printHeader(&sHeader);

#endif
               
               if(memcmp(sHeader.password, MD5Password, MD5_DIGEST_LENGTH) != 0)
               {
                   cout << "wrong password!";
                   msgCode= ERROR_WRONG_PASSWORD;
               }else{
                   
                   
                   //end checks
                   fileSizeMoved = sizeof(sHeader);
                   //if the file was to small
                   if(sHeader.fileSize <= sizeof(sHeader))
                       fileSizeMoved = sHeader.fileSize;
                   file.seekg (-fileSizeMoved, ios::end);
                   //Read the bytes moved to the end of the file
                   if(!file.read (reinterpret_cast<char*>(buffer),fileSizeMoved)){
                       cout << "error"; 
                       msgCode =  -1;
                   }
                   //Restoring the bytes moved to the end, again in their original possition
                   file.seekp (0, ios::beg);
                   file.write(reinterpret_cast<char*>(buffer), fileSizeMoved);
                   
                   file.close();
                   //Truncating the file to its oroginal size
                   truncate(fileName, sHeader.fileSize);
                   cout << "the complete file content is in memory";
                   printf("decrypting: %s and password: %s", fileName, password);
                   newFilePathAndName = strcat(newFilePath, sHeader.fileName);
                   rename(fileName, newFilePathAndName);
                   free(newFilePathAndName);
               }
           }
         
        
        }
    else {
        debug("Unable to open the file!");
        msgCode = ERROR_FILE_DOES_NOT_EXIST;
    }      
    debug("FINISHING DECRYPT");
    free(tempName);
    //  free(newFilePath);
    return msgCode ;
           
}

    