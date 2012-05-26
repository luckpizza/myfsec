//
//  EncryptorManager.cpp
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EncryptorManager.h"
#include "QuickEncode.h"
#include "secureHeader.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
#include "encryptUtils.h"
#include "Utils.h"
#include "AESEncrypt.h"
/**
 * This function verify if a file has the our internal structure (so it has been encrypted buy us
 * @param the fstream to the file we want to verify
 * @return OK if the file is our ERROR_NOT_SUPPORTED if not
 *
 */
int checkIfFileIsOurs(std::fstream* file ){
    int status = OK;
    
    (*file).seekg (0, std::ios::beg);
    secureHeader sHeader;
    //Checking if file is supported 
    if(!(*file).read (reinterpret_cast<char*>(&sHeader), sizeof(sHeader)))
    {
        std::cout << "File doesnt seem to be encrypted";
        status= ERROR_NOT_SUPPORTED;
    }else{
        printHeader(&sHeader);
        if(sHeader.signature != SIGNATURE || sHeader.version != VERSION || sHeader.headerSize != sizeof(sHeader)  )
        {
            std::cout << "File does not seems to be encrypted by us, sorry";
            status = ERROR_NOT_SUPPORTED;
        }
    }
    (*file).seekg (0, std::ios::beg);
    return status;
    
}


int checkIfFileIsOurs(const char* fileName ){
    int ret = FILE_EXIST;
    std::fstream file (fileName, std::ios::in | std::ios::out | std::ios::binary);
    if(file.is_open())
    {
        ret =  checkIfFileIsOurs(&file );
        
    }else{
        ret = ERROR_FILE_DOES_NOT_EXIST;
    }
    file.close();
    return ret;
}

int encodeDispacher(const char *fileName,const  char * password, int secureLevel, int securityType){
    secureHeader * sHeader = createHeaderForFile(fileName, password, securityType, secureLevel);
    if(sHeader == NULL){
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    if(sHeader->version == VERSION && sHeader->securityType == SECURITY_TYPE_QUICKENCODE){
        //return AES_encrypt(fileName, password, sHeader);
         return encodeQuick(fileName, password, sHeader);
    }
    myFree(sHeader);
    return ERROR_NOT_SUPPORTED;
}
int decodeDispacher(const char *fileName,const  char * password){
    secureHeader * sHeader = getHeaderFromFile(fileName);
    if(sHeader == NULL){
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    if(sHeader->version == VERSION && sHeader->securityType ==SECURITY_TYPE_QUICKENCODE){
        return decodeQuick(fileName, password);
    }
    return ERROR_NOT_SUPPORTED;
}


