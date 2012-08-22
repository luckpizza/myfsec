//
//  AppDelegate.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#define SMALL_VIEW 1
#define BIG_VIEW 2

@class ProgressBarViewController;
@interface AppDelegate : NSObject <NSApplicationDelegate>{
    NSButton *encryptButton;
    NSButton *dencryptButton;
    NSButton *chooseFile;
    
    NSTextField *filePath;
    NSTextField *password;
    NSTextField *rePassword;
    
    NSBox *securityLable;
    NSTextField * rePasswordLable;
    NSTextField *msgLable;
    NSMatrix *securityOption;
    int status;
    BOOL idle;


}
@property (assign) IBOutlet NSWindow *window;
@property (retain) IBOutlet NSTextField *filePath;
@property (retain) IBOutlet NSTextField *password;
@property (retain) IBOutlet NSTextField *rePassword;
@property (retain, nonatomic) IBOutlet NSButton *encryptButton;
@property (retain, nonatomic) IBOutlet NSButton *dencryptButton;
@property (retain) IBOutlet NSTextField *rePasswordLable;
@property (retain, nonatomic) IBOutlet NSBox *securityLable;
@property (retain, nonatomic) IBOutlet NSTextField *msgLable;
@property (retain, nonatomic) IBOutlet NSMatrix *securityOption;
@property (retain, nonatomic) ProgressBarViewController * progressBarViewController;
@property (retain, nonatomic) IBOutlet NSButton *keepUnencryptedFile;
@property (retain, nonatomic) IBOutlet NSButton *keepEncryptedFile;
@property (retain, nonatomic) IBOutlet NSButton * chooseFile;
@property ( ) int status;
@property (nonatomic) BOOL idle;
@property (nonatomic) int viewMoment;
//@property (nonatomic) IBAction

-(IBAction)encryptButtonPushed:(id)sender;
-(IBAction)dencryptButtonPushed:(id)sender;
-(IBAction)chooseFileButtonPushed:(id)sender;
-(void) setWindowToTypeOfFile;
- (void)encrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;
-(void) showStatusMsg;
-(void)progresIndicatorUpdater:(NSTimer *)timer;
-(IBAction)securityLevelChosen:(id)sender;

@end
