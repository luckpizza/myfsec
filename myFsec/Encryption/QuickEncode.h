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


int encodeQuick (const char *fileName, const char *password, secureHeader* sHeader) ;

int decodeQuick(const char *fileName, const char *password);


#endif
