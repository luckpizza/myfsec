//
//  FileUtils.cpp
//  myfsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "FileUtils.h"


/**
 * This function returns the file name from the given path (only the filename and extention)
 * @param path to the file we want to know the name
 * @return the name of the file. This pointer should be freed buy the user
 */

char * getFileNameFromPath(const char * path)
{
    char * tmp = (char *)myMalloc(strlen(path) + 1);
    memcpy(tmp, path, strlen(path) +1);
    char * lastPathRef = strrchr(tmp, '/');
    char * ret = (char *)myMalloc(strlen(lastPathRef)+ 1);
    strcpy(ret, lastPathRef);
    // *lastPathRef = '\0';
    free(tmp);
    debug( "name from path is + %s \n", ret);
    return ret;
    
}
/**
 * This function returns only the path with without the file name of a full path 
 * with a file name at the end (errase the last level)
 * @param path to the file we want to know the path
 * @return only the path without the last lvl. This should be freed but the user
 */
char * getOnlyPath(const char * path)
{
    char * ret = (char *)myMalloc(strlen(path) + 1);
    memcpy(ret, path, strlen(path) +1);
    char * lastPathRef = strrchr(ret, '/');
    *lastPathRef = '\0';
    debug("only path is= %s \n",ret);
    return ret;
    
    
}
