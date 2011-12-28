//
//  File.h
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_File_h
#define fsec_File_h

#define VERSION 1
#define DECODED 3
#define OK 1
#define FILE_EXIST 4
#define ENCODED 2
#define ERROR_NOT_SUPPORTED -1
#define ERROR_WRONG_PASSWORD -2
#define ERROR_FILE_DOES_NOT_EXIST -3
#define ERROR_PASSWORDS_DONT_MATCH -4
#define FSEC_EXTENTION ".myfsec"

int encodeQuick (const char *fileName,const  char * password);

int decodeQuick(const char *fileName, const char *password);

int checkIfFileIsOurs(const char* fileName );

#endif
