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
#include <openssl/sha.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "encryptUtils.h"
#include "QuickEncode.h"
#include "secureHeader.h"
#include "Utils.h"

/**
 * @function char * getFileNameFromPath(const char * path)
 * This function returns the file name from the given path 
 * (only the filename and extention) (IT RETURNS THE POINTER TO THE path argument)
 * @param path to the file we want to know the name
 * @return the name of the file.
 */
char * getFileNameFromPath(const char * path);

/**
 * @function char * get_only_path_copy(const char * path)
 * This function returns only the path with without the file name of a full path
 * with a file name at the end (errase the last level)
 * @param path to the file we want to know the path
 * @return only the path without the last lvl. This should be freed but the user
 */
char * get_only_path_copy(const char * path);

long get_filename_ext(const char *filename, char *ext);

const char * find_non_existing_file(const char* fileName);

/**
 *  @function char * file_name_generator(char *fileName, unsigned int amount)
 *  generates a random filename of the amount of letters
 *  indicated by amount.
 *  @param fileName a buffer big enought to store amount+1 letters
 *  @param amount of letters of the new name
 *  @return returns a pointer to fileName
 */

char * file_name_generator(char *fileName, int amount);

#endif
