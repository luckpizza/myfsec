//
//  MessageUtils.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 04/08/12.
//
//
#ifndef myfsec_MessageUtils_h
#define myfsec_MessageUtils_h
#include <Foundation/Foundation.h>
#include "StateCodes.h"

@interface MessageUtils : NSObject
+(NSString *) getEncodeMessage:(int) msgCode;

@end

#endif