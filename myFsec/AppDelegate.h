//
//  AppDelegate.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class ProgressBarViewController;
@interface AppDelegate : NSObject <NSApplicationDelegate>{
    NSButton *encryptButton;
    NSButton *dencryptButton;
    NSButton *chooseFile;
    
    NSTextField *filePath;
    NSTextField *password;
    NSTextField *rePassword;
    
    NSTextField *securityLable;
    NSTextField * rePasswordLable;
    NSTextField *msgLable;
    NSMatrix *securityOption;

}
@property (assign) IBOutlet NSWindow *window;
@property (retain) IBOutlet NSTextField *filePath;
@property (retain) IBOutlet NSTextField *password;
@property (retain) IBOutlet NSTextField *rePassword;
@property (retain, nonatomic) IBOutlet NSButton *encryptButton;
@property (retain, nonatomic) IBOutlet NSButton *dencryptButton;
@property (retain) IBOutlet NSTextField *rePasswordLable;
@property (retain, nonatomic) IBOutlet NSTextField *securityLable;
@property (retain, nonatomic) IBOutlet NSTextField *msgLable;
@property (retain, nonatomic) IBOutlet NSMatrix *securityOption;
@property (retain, nonatomic) IBOutlet NSProgressIndicator *progressBar;
@property (retain, nonatomic) ProgressBarViewController * progressBarViewController;
@property ( atomic) int status;
@property (nonatomic) BOOL idle;
//@property (nonatomic) IBAction

-(IBAction)encryptButtonPushed:(id)sender;
-(IBAction)dencryptButtonPushed:(id)sender;
-(IBAction)chooseFileButtonPushed:(id)sender;
-(NSString *) getEncodeMessage:(int) msgCode;
-(void) setWindowToTypeOfFile;
- (void)encrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void) showStatusMsg;
-(void)checkThem:(NSTimer *)timer;


@end
