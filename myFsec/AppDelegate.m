//
//  AppDelegate.m
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"
#import "QuickEncode.h"
#import "AESEncrypt.h"
#import "Encryptor.h"
#import "StateCodes.h"
#import "ProgressPanel.h"
//#import "EncryptorManager.h"

#define  DECODE_MSG @"File Decoded Succesful!!"
#define  ENCODED_MSG @"File Encoded Successfully!!"
#define  ERROR_NOT_SUPPORTED_MSG @"File is not encoded buy us, choos another file!"
#define  ERROR_WRONG_PASSWORD_MSG @"Wrong password!"
#define  ERROR_FILE_DOES_NOT_EXIST_MSG @"The file does not exist or can't be open!"
#define  ERROR_PASSWORDS_DONT_MATCH_MSG @"Passwords don't match, please verify your password"
extern long long _g_total_to_do;
extern long long _g_amount_done;


@implementation AppDelegate

@synthesize window = _window;
@synthesize password, rePassword, filePath, encryptButton, dencryptButton, rePasswordLable, securitySlider,fastLable, slowLable, lessSecureLable, moreSecureLable, securityLable, msgLable, securityOption;
@synthesize progressBar, status, progressPanel;



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
    [_window makeFirstResponder:chooseFile];
//    ProgressPanel * asd = [ProgressPanel new];
//    
//    NSWindow * pAbtWindow = [asd window];
//
//    [NSApp beginSheetModalForWindow:_window modalDelegate:self didEndSelector:@selector(didLoadBytes:loadComplete:) contextInfo:nil];
//      
    
//    [NSApp runModalForWindow: pAbtWindow];

   // [NSBundle loadNibNamed: @"ProgressPanel" owner: self];
//    [NSApp beginSheet: pAbtWindow
//       modalForWindow: _window
//        modalDelegate: self
//       didEndSelector: @selector(didEndSheet:returnCode:contextInfo:)
//          contextInfo: nil];
}

-(void) resetForm
{
    [self.progressBar setHidden:NO];
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
    [self.securityOption setHidden:YES];
}

- (int) getSecurityType:(long) option
{
    int rta = ERROR;
    switch (option) {
        case 0:
            rta = SECURITY_TYPE_QUICKENCODE;
            break;
        case 1:
            rta = SECURITY_TYPE_AES256;
            break;
        default:
            rta = ERROR;
            break;
    }
    return rta;
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
    [self.progressBar setHidden:YES];
    [_window makeFirstResponder:password];
    if(fileType == ERROR_FILE_DOES_NOT_EXIST)
    {
        [msgLable setStringValue:ERROR_FILE_DOES_NOT_EXIST_MSG];
        [self.encryptButton setEnabled:NO];
        [self.dencryptButton setEnabled:NO];
        //TODO: IF FILE DOES NOT EXIST
    }else if( fileType == ERROR_NOT_SUPPORTED)
    {        
        [self.progressBar setHidden:NO];
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
        [self.securityOption setHidden:NO];
    }else if( fileType == OK)
    {
        [self.progressBar setHidden:NO];
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
-(void)encode{

    long option = [securityOption selectedTag];
    status =[Encryptor encodeDispacher:filePath.stringValue password:password.stringValue securityType:[self getSecurityType:option]];
}
-(IBAction)encryptButtonPushed:(id)sender
{
    status = 0;
    NSTimer *timer;
    int msgCode= 1;
    long option = [securityOption selectedTag];
    NSLog(@"option is: %ld", option);
    if([[password stringValue] compare:[rePassword stringValue]] != 0)
    {
        msgCode = ERROR_PASSWORDS_DONT_MATCH;
        [self showStatusMsg];

    }else{
        [self performSelectorInBackground:@selector(encode) withObject:nil];
        timer = [NSTimer scheduledTimerWithTimeInterval:0.5 
                                                 target:self selector:@selector(checkThem:) 
                                               userInfo:nil repeats:YES] ;
        [timer fire];
    }
    


//    alert = [NSAlert alertWithMessageText:[self getEncodeMessage:msgCode] defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""   ]; 
//
//    [alert setAlertStyle:NSInformationalAlertStyle];
//    
//    [alert runModal];
//    if(msgCode == ENCODED)
//        [self resetForm];

    //   encodeQuick([filePath.stringValue UTF8String], [password.stringValue UTF8String]);
}


-(void)decode{
        status =[Encryptor decodeQuick:filePath.stringValue password:password.stringValue ];
}

-(IBAction)dencryptButtonPushed:(id)sender
{
    
    status = 0;
    NSTimer *timer;

    if([password stringValue] ==  nil)
    {
        status = ERROR_PASSWORD;
        [self showStatusMsg];
        
    }else{
        [self performSelectorInBackground:@selector(decode) withObject:nil];
        timer = [NSTimer scheduledTimerWithTimeInterval:0.5 
                                                 target:self selector:@selector(checkThem:) 
                                               userInfo:nil repeats:YES] ;
        [timer fire];
    }
            
}

-(IBAction)chooseFileButtonPushed:(id)sender
{
    
    
//    ASLogDebug(@"Show file open panel");
    
    NSString *dir = nil;
    
    NSOpenPanel *openDlg = [NSOpenPanel openPanel];
    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    // Disable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];
 //   ProgressPanelViewController * panel = [ProgressPanelViewController new];
//    if( progressPanel == nil)
//        progressPanel = [[ProgressPanel alloc]init];
//    //    progressPanel = [[ProgressPanelViewController alloc]initWithWindowNibName:@"ProgressPanel"];
//  
//    
//    
//    //create the file name label
//    NSTextField* newFileNameLabel = [[NSTextField alloc] initWithFrame:NSMakeRect(10, 10, 300.0, 20.0)];
//    //set properties
//    [newFileNameLabel setBordered: NO];
//    [newFileNameLabel setTextColor: [NSColor whiteColor]];
//    [newFileNameLabel setDrawsBackground:NO];
//    [newFileNameLabel setEditable:NO];
//    [newFileNameLabel setStringValue: @"File Name:"];
//    
//  //  [[progressPanel attachedSheet ] addSubview:newFileNameLabel];
////    NSWindow *asd = [[NSWindow alloc]init];
//    [[NSApplication sharedApplication] beginSheet:progressPanel.window modalForWindow:_window modalDelegate:self didEndSelector:nil contextInfo:nil];
//    [[NSApplication sharedApplication] runModalForWindow: progressPanel];

    //  [[NSApplication sharedApplication] runModalForWindow: progressPanel];

 //   [NSBundle loadNibNamed: @"ProgressPanel" owner: self];

 //  [NSApp beginSheet:progressPanel  modalForWindow:_window modalDelegate:self didEndSelector:nil contextInfo:nil];
   // [NSApp runModalForWindow:[progressPanel window]];
    [openDlg beginSheetModalForWindow:_window completionHandler:^(NSInteger result){
        if (result == NSFileHandlingPanelOKButton) {
          
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
    }];
    {
    //VIM COMDE
//    [panel setAllowsMultipleSelection:YES];
////    [panel setAccessoryView:showHiddenFilesView()];
//#if (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_6)
//    // NOTE: -[NSOpenPanel runModalForDirectory:file:types:] is deprecated on
//    // 10.7 but -[NSOpenPanel setDirectoryURL:] requires 10.6 so jump through
//    // the following hoops on 10.6+.
//    dir = [dir stringByExpandingTildeInPath];
//    if (dir) {
//        NSURL *dirURL = [NSURL fileURLWithPath:dir isDirectory:YES];
//        if (dirURL)
//            [panel setDirectoryURL:dirURL];
//    }
//    
//    NSInteger result = [panel runModal];
//#else
//    NSInteger result = [panel runModalForDirectory:dir file:nil types:nil];
//#endif
//    if (NSOKButton == result) {
//        // NOTE: -[NSOpenPanel filenames] is deprecated on 10.7 so use
//        // -[NSOpenPanel URLs] instead.  The downside is that we have to check
//        // that each URL is really a path first.
//        NSMutableArray *filenames = [NSMutableArray array];
//        NSArray *urls = [panel URLs];
//        NSUInteger i, count = [urls count];
//        for (i = 0; i < count; ++i) {
//            NSURL *url = [urls objectAtIndex:i];
//            if ([url isFileURL]) {
//                NSString *path = [url path];
//                if (path)
//                    [filenames addObject:path];
//            }
//        }
//        
//        if ([filenames count] > 0)
//            [self application:NSApp openFiles:filenames];
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

- (void) alertDidEnd:(NSAlert *) alert returnCode:(int) returnCode contextInfo:(int *) contextInfo{
    if(status == ENCODED || status == DECODED)
        [self resetForm];

}

-(void) showStatusMsg
{
    NSAlert * alert = [NSAlert alertWithMessageText:[self getEncodeMessage:status] defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""   ]; 
    [alert setAlertStyle:NSInformationalAlertStyle];
    [alert beginSheetModalForWindow:_window modalDelegate:self didEndSelector:@selector(alertDidEnd:returnCode:contextInfo:) contextInfo:nil];
    
}


-(void)checkThem:(NSTimer *)timer { 
    double progress;
    if(timer != nil){
        if(_g_amount_done == 0 || _g_total_to_do == 0){
            progress = 0.0;
            
        }else{
            progress = (_g_amount_done *100.0) / _g_total_to_do;
            
        }
        [progressBar setDoubleValue:progress];
        NSLog(@"progress: %f total+ %lld, done %lld", progress,_g_total_to_do,  _g_amount_done);
        if(progress < 100.0){
            return;
        }
    }
    [timer invalidate];
    [self showStatusMsg];
}


@end
