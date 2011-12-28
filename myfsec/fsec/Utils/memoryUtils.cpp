//
//  memoryUtils.cpp
//  fsec
//
//  Created by Lucas PIzzagalli on 8/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Utils.h"

void memoryErrorHandler();

void memoryErrorHandler()
{
    error("MEMORY ERROR!");
    exit(-1);
}
void * myMalloc(unsigned long size)
{
    void * ret = NULL;
    int i = 0;
    debug("Using myMalloc");
    while (i++ < 4) {
        if((ret = malloc(size))){
            return ret; 
        }
    }
     memoryErrorHandler();
    //ONLY TO AVOID WARNING. THIS SHOULD NEVER BEEN REACH
    return NULL;

}

void * myCalloc (unsigned long amount, unsigned long size)
{
    void * ret = NULL;
    int i = 0;
    while (i++ < 4) {
        if((ret = calloc(amount, size))){
            return ret; 
        }
    }
    memoryErrorHandler();
    //ONLY TO AVOID WARNING. THIS SHOULD NEVER BEEN REACH
    return NULL;

}



