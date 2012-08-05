//
//  MessageUtils.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 04/08/12.
//
//
#ifndef myfsec_MessageUtils_h
#define myfsec_MessageUtils_h

#import <Foundation/Foundation.h>

@interface MessageUtils : NSObject
+(NSString *) getEncodeMessage:(int) msgCode;

@end

#endif