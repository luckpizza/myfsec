//
//  debugLog.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/22/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef fsec_debugLog_h
#define fsec_debugLog_h
#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG1
#define debug(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...)
#endif
#endif
#ifdef INFO
#define info(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
#define info(fmt, ...)
#endif
#ifndef NO_ERROR
#define error(fmt, ...) fprintf(stderr,fmt, ##__VA_ARGS__)
#else
#define error(fmt, ...)
#endif


#ifndef RELEASE
#define myFree(x) free(x); x = NULL
#else
#define myFree(x) free(x)
#endif
