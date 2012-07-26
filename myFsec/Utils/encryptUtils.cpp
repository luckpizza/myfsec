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


// Print the MD5 sum as hex-digits.
//DEPRECATED
//void print_md5_sum(unsigned char* md) {
//    int i;
//    for(i=0; i <MD5_DIGEST_LENGTH; i++) {
//        printf("%02x",md[i]);
//    }
//}
void print_sha256_sum(unsigned char* md) {
    int i;
    for(i=0; i <SHA256_DIGEST_LENGTH; i++) {
        printf("%02x",md[i]);
    }
}
//DEPRECATED
//void hash_md5(unsigned char* password,unsigned char * MD5Password)
//{
//     char * passwordAndSalt =  ( char *)myMalloc(strlen((( const char*)password)) + strlen(SALT) + 1);
//    strcpy(passwordAndSalt, SALT);
//    strcat(passwordAndSalt, (const char*)password);
//    MD5((unsigned char*) passwordAndSalt, strlen(passwordAndSalt), MD5Password);
//
//}

void hash_sha256(unsigned char* password,int lenght, unsigned char * SHA256Password){
    SHA256((unsigned char*) password, lenght, SHA256Password);

}

void hash_sha256_salt(unsigned char* password, char* salt,int salt_length, unsigned char * SHA256Password)
{
    char * passwordAndSalt =  ( char *)myMalloc(strlen((( const char*)password)) + salt_length + 1);
    memcpy(passwordAndSalt, salt, salt_length);
    passwordAndSalt[salt_length] = '\0';
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
/**
 *  xorg_bytes:
 * Does the xor byte by byte of the 2 given arrays and stores the result in dst
 * return OK if no error paramenter, ERROR if error;
 */

int xor_bytes(const char * src1, int src1_lenght, const char * src2, int src2_lenght, char * dst)
{
    int i = 0;
    if(src1 == NULL || src2 == NULL || src1 <= 0 || src2 <= 0)
        return ERROR;
    while( i < src2_lenght && i < src1_lenght){
        dst[i] = src1[i] ^ src2[i];
        ++i;
    }
    return OK;
}

int random_k_bytes(char * bytes, int k)
{
    int i = 0;
    int tmp = 0;
    int to_copy = 0;
   if(k <= 0 )
       return ERROR;
    for (i = 0; i < k; i+=sizeof(int)) {
        tmp = rand();
        k - i < sizeof(int) ?to_copy=k-i:to_copy = sizeof(int);
        memcpy(&bytes[i], &tmp, to_copy);
    }
    return OK;
}
                         
//void sprint_md5_sum(unsigned char* md) {
///*    int i;
//    for(i=0; i <MD5_DIGEST_LENGTH; i++) {
//        sprintf("%02x",md[i]);
//    }
//*/
//}