//
//  FileUtils.cpp
//  myfsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "FileUtils.h"
#include "encryptUtils.h"


/**
 * @function char * getFileNameFromPath(const char * path)
 * This function returns the file name from the given path (only the filename and extention)
 * @param path to the file we want to know the name
 * @return the name of the file.
 */
char * getFileNameFromPath(const char * path)
{
    
    return (strrchr(path, '/')) + 1;
}


/**
 * @function char * get_only_path_copy(const char * path)
 * This function returns only the path with without the file name of a full path 
 * with a file name at the end (errase the last level)
 * @param path to the file we want to know the path
 * @return only the path without the last lvl. This should be freed but the user
 */
char * get_only_path_copy(const char * path)
{
    char * ret = (char *)myMalloc(strlen(path) + 1);
    memcpy(ret, path, strlen(path) +1);
    char * lastPathRef = strrchr(ret, '/');
    *(lastPathRef + 1) = '\0';
    debug("only path is= %s \n",ret);
    return ret;
}

long get_filename_ext(const char *filename, char *ext) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return 0;
    ext = (char*)myMalloc(strlen(dot) + 1);
    strcpy(ext, dot);
    return dot -filename ;
}

/**
 *  TODO: THIS may be an interesting function to have!
 */
const char * find_non_existing_file(const char* fileName)
{
    return fileName;
    //    fstream file;
    //    char * ext;
    //    file.open(fileName, ios_base::in);
    //    if(!file.good()){
    //        return fileName;
    //    }
    //    long index = 0;
    //
    //    while (file.good()){
    //        file.close();
    //       index = get_filename_ext(fileName, ext);
    //    } 1160151200
}

/**
 *  @function char * file_name_generator(char *fileName, unsigned int amount)
 *  generates a random filename of the amount of letters
 *  indicated by amount.
 *  @param fileName a buffer big enought to store amount+1 letters
 *  @param amount of letters of the new name
 *  @return returns a pointer to fileName
 */

char * file_name_generator(char *fileName, unsigned int amount)
{
    int tmp = rand();
    unsigned char diggest[SHA256_DIGEST_LENGTH];
    hash_sha256((unsigned char*)&tmp,sizeof(int), diggest);
    memcpy(fileName, diggest, amount > SHA256_DIGEST_LENGTH?SHA256_DIGEST_LENGTH:amount);
    return fileName;
}