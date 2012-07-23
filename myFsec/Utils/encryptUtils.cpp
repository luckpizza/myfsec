//
//  encryptUtils.c
//  fsec
//
//  Created by Lucas PIzzagalli on 8/22/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include "encryptUtils.h"
#include "Utils.h"

#define SALT "*&^%"    
unsigned char result[MD5_DIGEST_LENGTH];

// Print the MD5 sum as hex-digits.
void print_md5_sum(unsigned char* md) {
    int i;
    for(i=0; i <MD5_DIGEST_LENGTH; i++) {
        printf("%02x",md[i]);
    }
}
void print_sha256_sum(unsigned char* md) {
    int i;
    for(i=0; i <SHA256_DIGEST_LENGTH; i++) {
        printf("%02x",md[i]);
    }
}

void hash_md5(unsigned char* password,unsigned char * MD5Password)
{
     char * passwordAndSalt =  ( char *)myMalloc(strlen((( const char*)password)) + strlen(SALT) + 1);
    strcpy(passwordAndSalt, SALT);
    strcat(passwordAndSalt, (const char*)password);
    MD5((unsigned char*) passwordAndSalt, strlen(passwordAndSalt), MD5Password);

}

void hash_sha256(unsigned char* password,unsigned char * SHA256Password){
    SHA256((unsigned char*) password, strlen((char*)password), SHA256Password);

}

void hash_sha256_salt(unsigned char* password,unsigned char * SHA256Password)
{
    char * passwordAndSalt =  ( char *)myMalloc(strlen((( const char*)password)) + strlen(SALT) + 1);
    strcpy(passwordAndSalt, SALT);
    strcat(passwordAndSalt, (const char*)password);
    SHA256((unsigned char*) passwordAndSalt, strlen(passwordAndSalt), SHA256Password);

}

char * add_myFsec_extention_string(const char * fileName){
    char * temp = (char *)myMalloc(strlen(fileName) + strlen(FSEC_EXTENTION) + 1);
    strcpy(temp, fileName);
    strcat(temp, FSEC_EXTENTION);
    return temp;
}

void addMyFsecExtention(const char * fileName){
    char * temp = add_myFsec_extention_string(fileName);
    rename(fileName, temp);
    myFree(temp);

}

void recoverOldExtention(const char *fileName, secureHeader * sHeader){
    char * newFilePath = get_only_path_copy(fileName);
    newFilePath = (char*) myRealloc(newFilePath, strlen(newFilePath) + strlen(sHeader->fileName) + 1);
     strcat(newFilePath, sHeader->fileName);
    printHeader(sHeader);
    fprintf(stderr, "newFile is %s", newFilePath);
    rename(fileName, newFilePath);
    myFree(newFilePath);
}
char * recover_old_extention_copy(const char *fileName, secureHeader * sHeader){
    char * newFilePath = get_only_path_copy(fileName);
    newFilePath = (char*) myRealloc(newFilePath, strlen(newFilePath) + strlen(sHeader->fileName) + 1);
    strcat(newFilePath, sHeader->fileName);
    return newFilePath;
}
                         
//void sprint_md5_sum(unsigned char* md) {
///*    int i;
//    for(i=0; i <MD5_DIGEST_LENGTH; i++) {
//        sprintf("%02x",md[i]);
//    }
//*/
//}