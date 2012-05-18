//
//  ServiceHandler.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ServiceHandler : NSObject
- (void)encrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;

@end
