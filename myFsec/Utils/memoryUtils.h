//
//  memoryUtils.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_memoryUtils_h
#define fsec_memoryUtils_h


void * myMalloc(unsigned long size);
void * myCalloc (unsigned long amount, unsigned long size);
void * myRealloc(void * pointer, unsigned long size);


#endif
