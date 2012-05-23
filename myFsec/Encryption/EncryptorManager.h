//
//  EncryptorManager.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef myFsec_EncryptorManager_h
#define myFsec_EncryptorManager_h

#include <iostream>
#include <fstream>

#define SIGNATURE 111188
#define VERSION 1

int checkIfFileIsOurs(const char* fileName );
int checkIfFileIsOurs(std::fstream* file );
int encodeDispacher(const char *fileName,const  char * password, int version, int securityType);

int decodeDispacher(const char *fileName,const  char * password);

#endif
