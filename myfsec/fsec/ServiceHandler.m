//
//  ServiceHandler.m
//  fsec
//
//  Created by Lucas PIzzagalli on 8/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ServiceHandler.h"
#import "Encryptor.h"

@implementation ServiceHandler

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}
    
- (void)simpleEncrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error {
    
    // Test for strings on the pasteboard.
    NSLog(@"HEYYYYYY");
    NSArray *classes = [NSArray arrayWithObject:[NSString class]];
    NSDictionary *options = [NSDictionary dictionary];
    
    if (![pboard canReadObjectForClasses:classes options:options]) {
        *error = NSLocalizedString(@"Error: couldn't encrypt text.",
                                   @"pboard couldn't give string.");
        return;
    }
    
    // Get and encrypt the string.
    NSString *pboardString = [pboard stringForType:NSPasteboardTypeString];
    Encryptor * encryptor = [[Encryptor alloc]init];
    [encryptor encodeQuick:pboardString password:@"test"];
        
}

@end
