//
//  AESEncrypt.cpp
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string.h>
#include "AESEncrypt.h"
#include "Utils.h"
#include <openssl/aes.h>
#include <fstream>
#include "QuickEncode.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "encryptUtils.h"
#include "Utils.h"
#include "EncryptorManager.h"
#include <openssl/sha.h>

#define IV_SIZE  8
extern long long  _g_total_to_do;
extern long long _g_amount_done;
using namespace std;
void init_ctr(struct ctr_state *state, const unsigned char iv[8]);
const char * findNoExistingFile(const char* fileName);


struct ctr_state {
    unsigned char ivec[AES_BLOCK_SIZE];  /* ivec[0..7] is the IV, ivec[8..15] is the big-endian counter */
    unsigned int num;
    unsigned char ecount[AES_BLOCK_SIZE];
};

void init_ctr(struct ctr_state *state, const unsigned char iv[8])
{
    /* aes_ctr128_encrypt requires 'num' and 'ecount' set to zero on the
     * first call. */
    state->num = 0;
    memset(state->ecount, 0, AES_BLOCK_SIZE);
    
    /* Initialise counter in 'ivec' to 0 */
    memset(state->ivec + 8, 0, 8);
    
    /* Copy IV into 'ivec' */
    memcpy(state->ivec, iv, 8);
}


const char * findNoExistingFile(const char* fileName)
{
    return fileName;
    //    fstream file;
//    char * ext;
//    file.open(fileName, ios_base::in);
//    if(!file.good()){
//        return fileName;
//    }
    //    long index = 0;
    //    
    //    while (file.good()){
    //        file.close();
    //       index = get_filename_ext(fileName, ext);
    //    }
}

int AES_encrypt (const char *fileName, const char *password, secureHeader* sHeader)
{
    unsigned char SHA256Password[SHA256_DIGEST_LENGTH];
    if(fileName == NULL || *fileName == '\0' || sHeader == NULL)
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    
    hash_sha256((unsigned char*) password, SHA256Password);
  
    unsigned long sizeReaded;
    char buffer_in[AES_BLOCK_SIZE];
    unsigned char buffer_out[AES_BLOCK_SIZE];
   // memset(buffer_out, 0, 5*AES_BLOCK_SIZE);
    char * newFileName = add_myFsec_extention_string(fileName);
    //    memset(buffer, 0, sizeof(secureHeader));
    fstream file_in (fileName, ios::in | ios::binary);
    ofstream file_out (newFileName, ios::out | ios::binary);
    
    sHeader->extraSize = IV_SIZE;
    sHeader->extra.extra = myMalloc(IV_SIZE);
    _g_total_to_do = sHeader->fileSize;
    unsigned char iv[8];
    struct ctr_state state;
    
    
    
    srand((unsigned int)time(NULL));
    int random = rand();
    memcpy(iv, &random, 4);
    random = rand();
    memcpy(&iv[4], &random, 4);
    memcpy(sHeader->extra.extra, iv, IV_SIZE);
    
    
    init_ctr(&state, iv);
    AES_KEY aes_key;
    

    if (AES_set_encrypt_key(SHA256Password, SHA256_DIGEST_LENGTH * 8, &aes_key)){
        /* Handle the error */;
        //TODO: 
        return ERROR_WRONG_PASSWORD;
    }
    
    if (file_in.is_open() && file_out.is_open())
    {
        file_in.seekg (0);
        file_out.write(reinterpret_cast<char*>(sHeader), sHeader->headerSize);
        file_out.write(reinterpret_cast<char*>(sHeader->extra.extra), sHeader->extraSize);
        
        //Writing first sizeof(secureHeader) bytes to the end of the file
        
        while((sizeReaded = file_in.readsome(buffer_in, AES_BLOCK_SIZE)) != 0){
            AES_ctr128_encrypt((const unsigned char*)buffer_in, (unsigned char*)buffer_out, (const unsigned long)sizeReaded , &aes_key, state.ivec, state.ecount, &state.num);
            file_out.write((const char*)buffer_out, sizeReaded);
            _g_amount_done = file_in.tellg() ;
            
        }
        
        
        
        
        //Writting header to file
        file_out.flush();
        file_in.close();
        file_out.close();
        
    } else {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    debug("FINISHING ENCRYPT");
    return ENCODED;
    
}


int AES_decrypt (const char *fileName, const char *password, secureHeader* sHeader){
    unsigned char SHA256Password[SHA256_DIGEST_LENGTH];
    
    if(fileName == NULL || *fileName == '\0' || sHeader == NULL)
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    
    unsigned long sizeReaded;
    long long totalDone = 0;
    char buffer_in[AES_BLOCK_SIZE];
    unsigned char buffer_out[ AES_BLOCK_SIZE];
    hash_sha256((unsigned char*) password, SHA256Password);
    
    char * newFileName = recover_old_extention_copy(fileName, sHeader);
    fstream file_in (fileName, ios::in | ios::binary);
    ofstream file_out (newFileName, ios::out | ios::binary);
    
    if (!file_in.is_open() || !file_out.is_open())
    {
        return ERROR_FILE_DOES_NOT_EXIST;
    }
    file_in.seekg (0);
    file_in.seekg (sizeof(secureHeader));
    sHeader->extra.extra = myMalloc(sHeader->extraSize);
    if(!file_in.read((char*)(sHeader->extra.extra), sHeader->extraSize)){
        return ERROR_FILE_DOES_NOT_EXIST;
    };
    unsigned char iv[8];
    struct ctr_state state;
    
    memcpy(iv, sHeader->extra.extra, IV_SIZE);
    
    //memset(iv, 0, IV_SIZE);
    
    init_ctr(&state, iv);
    AES_KEY aes_key;
    
    if (AES_set_encrypt_key(SHA256Password, SHA256_DIGEST_LENGTH * 8, &aes_key)){
        return ERROR_WRONG_PASSWORD;
    }
    _g_total_to_do = sHeader->fileSize;
    while((sizeReaded = file_in.readsome(buffer_in, AES_BLOCK_SIZE)) != 0){
        AES_ctr128_encrypt((const unsigned char*)buffer_in, (unsigned char*)buffer_out, (const unsigned long)sizeReaded , &aes_key, state.ivec, state.ecount, &state.num);
        file_out.write((const char*)buffer_out, sizeReaded);
        totalDone +=sizeReaded;
        _g_amount_done = totalDone ;
    }    
    file_out.flush();
    file_in.close();
    file_out.close();

    debug("FINISHING ENCRYPT");
    return DECODED;
    
}

