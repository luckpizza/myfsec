//
//  AppDelegate.m
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"
#import "QuickEncode.h"
#import "Encryptor.h"
#import "StateCodes.h"


#define  DECODE_MSG @"File Decoded Succesful!!"
#define  ENCODED_MSG @"File Encoded Successfully!!"
#define  ERROR_NOT_SUPPORTED_MSG @"File is not encoded buy us, choos another file!"
#define  ERROR_WRONG_PASSWORD_MSG @"Wrong password!"
#define  ERROR_FILE_DOES_NOT_EXIST_MSG @"The file does not exist or can't be open!"
#define  ERROR_PASSWORDS_DONT_MATCH_MSG @"Passwords don't match, please verify your password"

@implementation AppDelegate

@synthesize window = _window;
@synthesize password, rePassword, filePath, encryptButton, dencryptButton, rePasswordLable, securitySlider,fastLable, slowLable, lessSecureLable, moreSecureLable, securityLable, msgLable;

-(BOOL)application:(NSApplication *)app openFile:(NSString *)filename
{
    
    [filePath setStringValue:filename];
    [self setWindowToTypeOfFile];
    NSLog(@"File name %@", filename);
    return YES;
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    //Service Provider declaration and update of system services
    [NSApp setServicesProvider: self];
    NSUpdateDynamicServices();

}

-(void) resetForm
{

    [self.dencryptButton setHidden:YES];
    [self.encryptButton setHidden:YES];
    [self.rePasswordLable setHidden:YES];
    [self.rePassword setHidden:YES];
    [self.lessSecureLable setHidden:YES];
    [self.securitySlider setHidden:YES];
    [self.moreSecureLable setHidden:YES];
    [self.fastLable setHidden:YES];
    [self.slowLable setHidden:YES];
    [self.securityLable setHidden:YES];
    [self.rePasswordLable setHidden:YES];
    [self.rePassword setHidden:YES];
    [filePath setStringValue:@""];
    [password setStringValue:@""];
    [rePassword setStringValue:@""];
    [self.encryptButton setEnabled:YES];
    [self.dencryptButton setEnabled:YES];
    [self.msgLable setStringValue:@""];
    
}

-(void) controlTextDidChange: (NSNotification *)notification
{
    [self setWindowToTypeOfFile];
}

-(void) setWindowToTypeOfFile
{
    
    // filePath controlTextDidChange:
    NSString *fileName = [filePath stringValue];
    int fileType;
    fileType = [Encryptor checkIfFileIsOurs:fileName];
    [self.msgLable setStringValue:@""];
    if(fileType == ERROR_FILE_DOES_NOT_EXIST)
    {
        [msgLable setStringValue:ERROR_FILE_DOES_NOT_EXIST_MSG];
        [self.encryptButton setEnabled:NO];
        [self.dencryptButton setEnabled:NO];
        //TODO: IF FILE DOES NOT EXIST
    }else if( fileType == ERROR_NOT_SUPPORTED)
    {        
        [self.encryptButton setEnabled:YES];
        [self.dencryptButton setHidden:YES];
        [self.encryptButton setHidden:NO];
        [self.rePasswordLable setHidden:NO];
        [self.rePassword setHidden:NO];
        [self.lessSecureLable setHidden:NO];
        [self.securitySlider setHidden:NO];
        [self.moreSecureLable setHidden:NO];
        [self.fastLable setHidden:NO];
        [self.slowLable setHidden:NO];
        [self.securityLable setHidden:NO];
    }else if( fileType == OK)
    {
        [encryptButton setHidden:YES];
        [dencryptButton setEnabled:YES];
        [dencryptButton setHidden:NO];
        [self.rePasswordLable setHidden:YES];
        [self.rePassword setHidden:YES];
        
        //TODO: FILE TO DENCRYPT
    }else{
        //UNKNOW ERROR
    }
    
}
-(IBAction)pathFileFilled:(id)sender
{
    [self setWindowToTypeOfFile];
}

-(IBAction)encryptButtonPushed:(id)sender
{
    int msgCode= 1;
    NSAlert * alert;
    if([[password stringValue] compare:[rePassword stringValue]] != 0)
    {
        msgCode = ERROR_PASSWORDS_DONT_MATCH;
        
    }else{
        msgCode = [Encryptor encodeQuick:filePath.stringValue password:password.stringValue];     
    }
    alert = [NSAlert alertWithMessageText:[self getEncodeMessage:msgCode] defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""   ]; 

    [alert setAlertStyle:NSInformationalAlertStyle];
    
    [alert runModal];
    if(msgCode == ENCODED)
        [self resetForm];
    
    //   encodeQuick([filePath.stringValue UTF8String], [password.stringValue UTF8String]);
}

-(IBAction)dencryptButtonPushed:(id)sender
{
    int msgCode;
    NSLog(@"filepat is %@",filePath.stringValue);
    msgCode = [Encryptor decodeQuick:filePath.stringValue password:password.stringValue];                

    NSAlert * alert = [NSAlert alertWithMessageText:[self getEncodeMessage:msgCode] defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""   ]; 
    [alert setAlertStyle:NSInformationalAlertStyle];
    
    [alert runModal];
    
    if(msgCode == DECODED)
        [self resetForm];
    //    decodeQuick([filePath.stringValue UTF8String], [password.stringValue UTF8String]);
    
}

-(IBAction)chooseFileButtonPushed:(id)sender
{
    
    
    //int i; // Loop counter.
    
    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    // Disable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];
    
    // Display the dialog.  If the OK button was pressed,
    // process the files.
    [openDlg setAllowsMultipleSelection:NO] ;
    if ( [openDlg runModal] == NSOKButton )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg  filenames];
        
        // Loop through all the files and process them.
        
        NSString* fileName = [files objectAtIndex:0];
        [filePath setStringValue:fileName];
        NSLog(@"FileName is = %@", fileName);
        // Do something with the filename.
        [self setWindowToTypeOfFile];
        
        //    for( i = 0; i < [files count]; i++ )
        //    {
        //        NSString* fileName = [files objectAtIndex:i];
        //        [filePath setStringValue:fileName];
        //        NSLog(@"FileName is = %@", fileName);
        //        // Do something with the filename.
        //        [enc checkIfFileIsOurs:fileName];
        //    }
    }
    
}


-(NSString *) getEncodeMessage:(int) msgCode
{
    NSString * retMsg = @"ERROR";
    switch (msgCode) {
        case DECODED:
            retMsg =  DECODE_MSG;
            break;
        case ENCODED:
            retMsg = ENCODED_MSG;
            break;
        case  ERROR_NOT_SUPPORTED:
            retMsg =  ERROR_NOT_SUPPORTED_MSG;
            break;
        case ERROR_WRONG_PASSWORD:
            retMsg =  ERROR_WRONG_PASSWORD_MSG;
            break;
        case ERROR_FILE_DOES_NOT_EXIST:
            retMsg = ERROR_FILE_DOES_NOT_EXIST_MSG;
        case ERROR_PASSWORDS_DONT_MATCH:
            retMsg = ERROR_PASSWORDS_DONT_MATCH_MSG;
        default:
            break;
    }
    return retMsg;
    
    
    
    
    
}

/*
 *  Method called whenever the service is called
 */
- (void)encrypt:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error{
    
    if([[pboard types] containsObject:NSFilenamesPboardType])
    {
        NSArray *filenames=[pboard propertyListForType:NSFilenamesPboardType];
        NSString *fileName = [filenames objectAtIndex:0];
        [filePath setStringValue:fileName];
        [self setWindowToTypeOfFile];

    }
}

/**
 *  Close app when closing the window
 */
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
    return YES;
}


@end
