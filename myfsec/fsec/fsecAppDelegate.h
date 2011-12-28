//
//  fsecAppDelegate.h
//  fsec
//
//  Created by Lucas PIzzagalli on 7/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface fsecAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *_window;
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

}

@property (retain) IBOutlet NSWindow *window;
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


//@property (nonatomic) IBAction

-(IBAction)encryptButtonPushed:(id)sender;
-(IBAction)dencryptButtonPushed:(id)sender;
-(IBAction)chooseFileButtonPushed:(id)sender;
-(NSString *) getEncodeMessage:(int) msgCode;
-(void) setWindowToTypeOfFile;


@end
