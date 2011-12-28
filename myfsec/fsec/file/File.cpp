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
#include "File.h"
#include "secureHeader.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
#include "encryptUtils.h"
#include "Utils.h"

#define SIGNATURE 111188
#define SECURITY_TYPE 1
unsigned char MD5Password[MD5_DIGEST_LENGTH];


using namespace std;

ifstream::pos_type size;
//Some private declaration of functions
int checkIfFileIsOurs(fstream* file );
char * getFileNameFromPath(const char * path);
char * getOnlyPath(const char * path);


/**
 * This function verify if a file has the our internal structure (so it has been encrypted buy us
 * @param the fstream to the file we want to verify
 * @return OK if the file is our ERROR_NOT_SUPPORTED if not
 *
 */
int checkIfFileIsOurs(fstream* file ){
    int status = OK;
    
    (*file).seekg (0, ios::beg);
    secureHeader sHeader;
    //Checking if file is supported 
    if(!(*file).read (reinterpret_cast<char*>(&sHeader), sizeof(sHeader)))
    {
        cout << "File doesnt seem to be encrypted";
        status= ERROR_NOT_SUPPORTED;
    }
    else if(sHeader.signature != SIGNATURE || sHeader.version != VERSION || sHeader.headerSize != sizeof(sHeader)  )
    {
        cout << "File does not seems to be encrypted by us, sorry";
        status = ERROR_NOT_SUPPORTED;
    }
    (*file).seekg (0, ios::beg);
    return status;

}


int checkIfFileIsOurs(const char* fileName ){
    int ret = FILE_EXIST;
    fstream file (fileName, ios::in | ios::out | ios::binary);
    if(file.is_open())
    {
        ret =  checkIfFileIsOurs(&file );
        
    }else{
        ret = ERROR_FILE_DOES_NOT_EXIST;
    }
    return ret;
}

/**
 * This function returns the file name from the given path (only the filename and extention)
 * @param path to the file we want to know the name
 * @return the name of the file. This pointer should be freed buy the user
 */
 
char * getFileNameFromPath(const char * path)
{
    char * tmp = (char *)myMalloc(strlen(path) + 1);
    memcpy(tmp, path, strlen(path) +1);
    char * lastPathRef = strrchr(tmp, '/');
    char * ret = (char *)myMalloc(strlen(lastPathRef)+ 1);
    strcpy(ret, lastPathRef);
    // *lastPathRef = '\0';
    free(tmp);
    debug( "name from path is + %s \n", ret);
    return ret;
    
}
/**
 * This function returns only the path with without the file name of a full path 
 * with a file name at the end (errase the last level)
 * @param path to the file we want to know the path
 * @return only the path without the last lvl. This should be freed but the user
 */
char * getOnlyPath(const char * path)
{
    char * ret = (char *)myMalloc(strlen(path) + 1);
    memcpy(ret, path, strlen(path) +1);
    char * lastPathRef = strrchr(ret, '/');
    *lastPathRef = '\0';
    debug("only path is= %s \n",ret);
    return ret;
    
    
}

/**
 *
 * encode a file with the given password
 * @param fileName the file name that we want to encrypt
 * @param password the password that will be used to encrypt the file
 * @return ENCODED if ok, error otherwise
 */


int encodeQuick (const char *fileName, const char *password) {
    if(fileName == NULL || *fileName == '\0')
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }

    fstream file (fileName, ios::in | ios::out | ios::binary);
    secureHeader sHeader;
    long long sizeReaded;
    char *realFileName;
    char buffer[sizeof(sHeader)];
    memset(buffer, 0, sizeof(sHeader));
    encrypt_md5((unsigned char*) password, MD5Password);
    debug("hashed password is \n");
#ifdef DEBUG
    print_md5_sum(MD5Password);
#endif

    if (file.is_open() )
    {
        file.seekg(0, ios::end);
        long long size = file.tellg();
        file.seekg (0);
        if(!file.read (buffer, sizeof(sHeader)))
        {
            debug( "File is smaller than Header");//sizeof(sHeader));
            file.clear();
        }
        debug("number of bytes read =%ld \n size of the file= %lld", file.gcount(), size);
        sizeReaded =file.gcount();
        memcpy(sHeader.password, MD5Password, MD5_DIGEST_LENGTH);
        sHeader.signature = SIGNATURE;
        sHeader.version = VERSION;
        sHeader.fileSize = size;
        sHeader.headerSize = sizeof(sHeader);
        realFileName = getFileNameFromPath(fileName);
        memcpy(sHeader.fileName, realFileName, strlen(realFileName) + 1);
        free(realFileName);
        file.seekp(0,ios::beg);
        printHeader(&sHeader);
        file.write(reinterpret_cast<char*>(&sHeader), sizeof(sHeader) );
        file.seekp(0,ios::end);
        size = file.tellg();
        debug("we are moving to the end of the file: %lld \n",size );
        file.write(reinterpret_cast<char*>(buffer), sizeReaded);
        file.flush();
        file.close();
            
            cout << "the complete file content is in memory";
        debug("leido fue+ %s \n", buffer);
    } else {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    char * temp = (char *)myMalloc(strlen(fileName) + strlen(FSEC_EXTENTION) + 1);
    strcpy(temp, fileName);
    strcat(temp, FSEC_EXTENTION);
    rename(fileName, temp);
    free(temp);
    /*
        else cout << "Unable to open file";
        printf("file name was: %s and password: %s", fileName, password);
      */
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
           free(tempName);
           //  free(newFilePath);
           return msgCode ;
           
    }

    