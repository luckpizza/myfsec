//
//  File.h
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_File_h
#define fsec_File_h
#define SECURITY_TYPE_QUICKENCODE 1
#include "secureHeader.h"

/**
 * @function int encodeQuick (const char *fileName, const char *password, secureHeader* sHeader)
 * encode a file with the given password
 * @param fileName the file name that we want to encrypt
 * @param password the password that will be used to encrypt the file
 * @return ENCODED if ok, error otherwise
 */
int encodeQuick (const char *fileName, const char *password, secureHeader* sHeader) ;

/**
 * @function int decodeQuick(const char *fileName, const char *password, secureHeader * sHeader)
 * Decodes a file encrypted using the QuickEncode
 */
int decodeQuick(const char *fileName, const char *password, secureHeader* sHeader);


#endif
