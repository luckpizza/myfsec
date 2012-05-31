//
//  AppDelegate.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class ProgressPanel;
@interface AppDelegate : NSObject <NSApplicationDelegate>{
    NSButton *encryptButton;
    NSButton *dencryptButton;
    NSButton *chooseFile;
    
    NSTextField *filePath;
    NSTextField *password;
    NSTextField *rePassword;
    
    NSTextField *securityLable;
    NSTextField *fastLable;
    NSTextField *slowLable;
    NSTextField *moreSecureLable;
    NSTextField *lessSecureLable;
    NSSlider * securitySlider;
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
@property (retain, nonatomic) IBOutlet NSTextField *fastLable;
@property (retain, nonatomic) IBOutlet NSTextField *slowLable;
@property (retain, nonatomic) IBOutlet NSTextField *moreSecureLable;
@property (retain, nonatomic) IBOutlet NSTextField *lessSecureLable;
@property (retain, nonatomic) IBOutlet NSTextField *securityLable;
@property (retain, nonatomic) IBOutlet NSSlider * securitySlider;
@property (retain, nonatomic) IBOutlet NSTextField *msgLable;
@property (retain, nonatomic) IBOutlet NSMatrix *securityOption;
@property (retain, nonatomic) IBOutlet NSProgressIndicator *progressBar;
@property (retain, nonatomic) ProgressPanel * progressPanel;
@property ( atomic) int status;
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
