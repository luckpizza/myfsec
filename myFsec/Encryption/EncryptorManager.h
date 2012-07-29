//
//  EncryptorManager.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef myFsec_EncryptorManager_h
#define myFsec_EncryptorManager_h
#include "FileUtils.h"
#include "secureHeader.h"

#define SIGNATURE 111188
#define VERSION 1
#define CANCEL 11

/**
 * @function int checkIfFileIsOurs(std::fstream* file )
 * This function verify if a file has our internal structure (so it has been encrypted buy us
 * @param the fstream to the file we want to verify
 * @return OK if the file is our ERROR_NOT_SUPPORTED if not
 *
 */
int checkIfFileIsOurs(const char* fileName );

/**
 * @function int checkIfFileIsOurs(const char* fileName )
 * This function verify if a file exists, and has our internal structure (so it has been encrypted buy us
 * @param the fstream to the file we want to verify
 * @return OK if the file is our ERROR_NOT_SUPPORTED if not
 *
 */
int checkIfFileIsOurs(std::fstream* file );

/**
 * @function int encodeDispacher(const char *fileName,const  char * password, int secureLevel, int securityType)
 * Dispacher to decide how to encode the file, depending on the securityType.
 *  @param fileName The fileName of the file
 *  @param securityLevel NOT IMPLEMENTED
 *  @param SecurityType How to encode the file
 */
int encodeDispacher(const char *fileName,const  char * password, int secureLevel, int securityType);

/**
 * @function int decodeDispacher(const char *fileName,const  char * password)
 * Dispacher to decide how to decode the file, depending on the securityType(that is stored in the header).
 *  @param fileName The fileName of the file
 *
 */

int decodeDispacher(const char *fileName,const  char * password);
int initDecoderHeader(const char *fileName, const char *password, secureHeader * sHeader);

/**
 * @function void cancelProcess()
 * Call this function to notify the encrypting thread that it should stop
 * and cancel everything!
 */
void cancelProcess();
#endif
