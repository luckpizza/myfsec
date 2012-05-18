//
//  secureHeader.cpp
//  fsec
//
//  Created by Lucas PIzzagalli on 9/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "secureHeader.h"
#include "Utils.h"


void printHeader(secureHeader * sHeader)
{
    fprintf(stderr, "signature %d \n version %d \n password", sHeader->signature, sHeader->version);
    print_md5_sum(sHeader->password);
    fprintf(stderr, "\n headerSize %d \n file size: %lld \n file Name: %s \n", sHeader->headerSize, sHeader->fileSize, sHeader->fileName);
    
     
}