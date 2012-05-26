//
//  FileUtils.h
//  myfsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef myfsec_FileUtils_h
#define myfsec_FileUtils_h
#include <iostream>
#include <fstream>
#include "QuickEncode.h"
#include "secureHeader.h"
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
#include "encryptUtils.h"
#include "Utils.h"


char * getFileNameFromPath(const char * path);
char * getOnlyPath(const char * path);
long get_filename_ext(const char *filename, char *ext);
#endif
