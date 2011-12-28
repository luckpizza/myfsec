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
#include <openssl/md5.h>
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

void encrypt_md5(unsigned char* password,unsigned char * MD5Password)
{
     char * passwordAndSalt =  ( char *)myMalloc(strlen((( const char*)password)) + strlen(SALT) + 1);
    strcpy(passwordAndSalt, SALT);
    strcat(passwordAndSalt, (const char*)password);
    MD5((unsigned char*) passwordAndSalt, strlen(passwordAndSalt), MD5Password);

}

//void sprint_md5_sum(unsigned char* md) {
///*    int i;
//    for(i=0; i <MD5_DIGEST_LENGTH; i++) {
//        sprintf("%02x",md[i]);
//    }
//*/
//}