//
//  EncryptorManager.cpp
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>

#include "Utils.h"
#include "EncryptorManager.h"
#include "QuickEncode.h"
#include "secureHeader.h"
#include "AESEncrypt.h"
//#include "Encryptor.h"
#define DEBUG1 1
#import "EncryptionOptions.h"


using namespace std;
long long  _g_total_to_do;
long long _g_amount_done;
int cancel;

/**
 * @function int checkIfFileIsOurs(std::fstream* file )
 * This function verify if a file has our internal structure (so it has been encrypted buy us
 * @param the fstream to the file we want to verify
 * @return the securitytype if the file is our ERROR_NOT_SUPPORTED if not
 *
 */
int checkIfFileIsOurs(std::fstream* file ){
    int status = OK;
    
    (*file).seekg (0, std::ios::beg);
    secureHeader sHeader;
    //Checking if file is supported 
    if(!(*file).read (reinterpret_cast<char*>(&sHeader), sizeof(sHeader)))
    {
        error("File doesnt seem to be encrypted");
        status= ERROR_NOT_SUPPORTED;
    }else{
        printHeader(&sHeader);
        if(sHeader.signature != SIGNATURE || sHeader.version != VERSION || sHeader.headerSize != sizeof(sHeader)  )
        {
            error("File does not seems to be encrypted by us, sorry");
            status = ERROR_NOT_SUPPORTED;
        }
    }
    (*file).seekg (0, std::ios::beg);
    return status == OK?sHeader.securityType:status;
    
}

/**
 * @function int checkIfFileIsOurs(const char* fileName )
 * This function verify if a file exists, and has our internal structure (so it has been encrypted buy us
 * @param the fstream to the file we want to verify
 * @return the securitytype if the file is our ERROR_NOT_SUPPORTED if not or ERROR_FILE_DOES_NOT_EXIST 
 *
 */
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

/**
 * @function int encodeDispacher(const char *fileName,const  char * password, int secureLevel, int securityType)
 * Dispacher to decide how to encode the file, depending on the securityType.
 *  @param fileName The fileName of the file
 *  @param securityLevel NOT IMPLEMENTED
 *  @param SecurityType How to encode the file
 */
int encodeDispacher(const char *fileName,const  char * password, int secureLevel, int securityType, int keep_file){
    cancel = 0;
    secureHeader * sHeader = createHeaderForFile(fileName, password, securityType, secureLevel);
    int rta = ERROR;
    if(sHeader == NULL){
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    if(sHeader->version != VERSION){
        rta = ERROR_NOT_SUPPORTED_VERSION;
    }else if(sHeader->securityType == SECURITY_TYPE_AES256){
        rta =  AES_encrypt(fileName, password, sHeader);
        if(rta == ENCODED && keep_file == DONT_KEEP){
            remove(fileName);
        }
    }else if(sHeader->securityType == SECURITY_TYPE_QUICKENCODE){
        rta = encodeQuick(fileName, password, sHeader);
        addMyFsecExtention(fileName);
    }else{
        rta = ERROR_NOT_SUPPORTED_ENCRYPTION;
    }
    destroyHeader(sHeader);
    return rta;
}

/**
 * @function int decodeDispacher(const char *fileName,const  char * password)
 * Dispacher to decide how to decode the file, depending on the securityType(that is stored in the header).
 *  @param fileName The fileName of the file
 *  
 */
int decodeDispacher(const char *fileName,const  char * password, int keep_file){
    cancel = 0;
    secureHeader * sHeader = (secureHeader*)myMalloc(sizeof(secureHeader));
    int rta = ERROR;

    int status = initDecoderHeader(fileName, password, sHeader);
    if(status != DECODED){
        return status;
    }
    if(sHeader->version != VERSION){
        rta = ERROR_NOT_SUPPORTED_VERSION;
    }else if(sHeader->securityType == SECURITY_TYPE_AES256){
        rta =  AES_decrypt(fileName, password, sHeader);
        if(rta == DECODED && keep_file == DONT_KEEP){
            remove(fileName);
        }
    }else if(sHeader->securityType == SECURITY_TYPE_QUICKENCODE){
        rta = decodeQuick(fileName, password, sHeader);
    }else{
        rta = ERROR_NOT_SUPPORTED_ENCRYPTION;
    }
    destroyHeader(sHeader);
    return rta;
}



//int decodeChecks
int initDecoderHeader(const char *fileName, const char *password, secureHeader * sHeader){
    unsigned char SHA256Password[SHA256_DIGEST_LENGTH];

    //Make sure that the file that want to be dencrypted has the correct extention. 
    //    char * tempName = (char *)myMalloc(strlen(fileName) + 1);
    int error;
    //strcpy(tempName, fileName);
    char * extention = strrchr(fileName, '.');
    //   myFree(tempName);
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
    
    
    if((error = checkIfFileIsOurs(&file)) == ERROR_FILE_DOES_NOT_EXIST || error == ERROR_NOT_SUPPORTED)
    {
        debug("file seems not to be ours!");
        return error;
    }
    file.read (reinterpret_cast<char*>(sHeader), sizeof(secureHeader));
    hash_sha256_salt((unsigned char*) password,sHeader->salt, sHeader->saltLength, SHA256Password);
    debug("hashed password is \n");
    debugSHA256(SHA256Password);
    debug("password in the header is: \n");
#ifdef DEBUG
    debugSHA256(sHeader->password);
    debug("HEADER READ IS: \n");
    printHeader(sHeader);
    
#endif
    
    if(memcmp(sHeader->password, SHA256Password, SHA256_DIGEST_LENGTH) != 0)
    {
        debug( "wrong password!");
        return  ERROR_WRONG_PASSWORD;
    }
    printHeader(sHeader);

    file.close();
    return DECODED;
    
}

/**
 * @function void cancelProcess()
 * Call this function to notify the encrypting thread that it should stop
 * and cancel everything!
 */
void cancelProcess()
{
    cancel = CANCEL;
}

