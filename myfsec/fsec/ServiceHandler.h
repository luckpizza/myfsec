//
//  ServiceHandler.h
//  fsec
//
//  Created by Lucas PIzzagalli on 8/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ServiceHandler : NSObject
- (void)simpleEncrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;

@end
