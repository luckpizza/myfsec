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
#import "ProgressBarViewController.h"
//#import "EncryptorManager.h"

extern long long _g_total_to_do;
extern long long _g_amount_done;


@implementation AppDelegate

@synthesize window = _window;
@synthesize password, rePassword, filePath, encryptButton, dencryptButton, rePasswordLable, securityLable, msgLable, securityOption;
@synthesize progressBar, status, progressBarViewController, idle;



-(BOOL)application:(NSApplication *)app openFile:(NSString *)filename
{
    
    [filePath setStringValue:filename];
    [self setWindowToTypeOfFile];
    NSLog(@"File name %@", filename);
    return YES;
}



- (void)sheetDidEnd:(NSWindow *)sheet
         returnCode:(int)returnCode
        contextInfo:(void  *)contextInfo
{
    [[NSApplication sharedApplication] stopModal];
    [progressBarViewController.window orderOut:nil];
    [self showStatusMsg];

}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    //Service Provider declaration and update of system services
    [NSApp setServicesProvider: self];
    NSUpdateDynamicServices();
//    [_window makeFirstResponder:chooseFile];
  //  AppDelegate * del = [AppDelegate alloc
//    NSWindow * pAbtWindow = [asd window];
 //    [[NSApplication sharedApplication] runModalForWindow: asd.window ];//      
    
//    [NSApp runModalForWindow: asd];

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
    [self.rePasswordLable setHidden:YES];
    [self.rePassword setHidden:YES];
    [self.securityLable setHidden:YES];
    [self.securityOption setHidden:YES];

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
    while (!idle ) {
        usleep(100);
    }
    [[NSApplication sharedApplication] endSheet:progressBarViewController.window];
    [[NSApplication sharedApplication] stopModal];
    [progressBarViewController.window orderOut:nil];
    [progressBarViewController.window close];
//    [progressBarViewController close];
//    [self showStatusMsg];

}
-(IBAction)encryptButtonPushed:(id)sender
{
    status = 0;
    NSTimer *timer;
    idle= FALSE;
    long option = [securityOption selectedTag];
    NSLog(@"option is: %ld", option);
    if([[password stringValue] compare:[rePassword stringValue]] != 0)
    {
        status = ERROR_PASSWORDS_DONT_MATCH;
        [self showStatusMsg];

    }else{
        [self performSelectorInBackground:@selector(encode) withObject:nil];
        timer = [NSTimer scheduledTimerWithTimeInterval:0.5 
                                                 target:self selector:@selector(checkThem:) 
                                               userInfo:nil repeats:YES] ;
        progressBarViewController = [[ProgressBarViewController alloc] initWithWindowNibName:@"ProgressPanel"];
        [[NSApplication sharedApplication] beginSheet: progressBarViewController.window
                                       modalForWindow: _window
                                        modalDelegate: self
                                       didEndSelector: @selector(sheetDidEnd:returnCode:contextInfo:)
                                          contextInfo: nil];

        [timer fire];
    }
    
}


-(void)decode{
    status =[Encryptor decodeDispacher:filePath.stringValue password:password.stringValue ];
    while (!idle ) {
        sleep(1);
    }

    [NSApp endSheet:progressBarViewController.window];
    [[NSApplication sharedApplication] stopModal];
    [progressBarViewController.window orderOut:nil];
    [progressBarViewController close];
    [[NSApplication sharedApplication] abortModal];

}

-(IBAction)dencryptButtonPushed:(id)sender
{
    
    status = 0;
    NSTimer *timer;
    idle = FALSE;
    if([password stringValue] ==  nil)
    {
        status = ERROR_PASSWORD;
        [self showStatusMsg];
        
    }else{
        [self performSelectorInBackground:@selector(decode) withObject:nil];
        timer = [NSTimer scheduledTimerWithTimeInterval:0.5 
                                                 target:self selector:@selector(checkThem:) 
                                               userInfo:nil repeats:YES] ;
        
        progressBarViewController = [[ProgressBarViewController alloc] initWithWindowNibName:@"ProgressPanel"];
        [[NSApplication sharedApplication] beginSheet: progressBarViewController.window
                                       modalForWindow: _window
                                        modalDelegate: self
                                       didEndSelector: @selector(sheetDidEnd:returnCode:contextInfo:)
                                          contextInfo: nil];
        

        [timer fire];
    }
            
}

-(IBAction)chooseFileButtonPushed:(id)sender
{
    
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
    [_window makeKeyAndOrderFront:alert];
}


-(void)checkThem:(NSTimer *)timer { 
    double progress;
    if(timer != nil){
        if(_g_amount_done == 0 || _g_total_to_do == 0){
            progress = 0.0;
            
        }else{
            progress = (_g_amount_done *100.0) / _g_total_to_do;
            
        }
        [progressBarViewController.progressIndicator setDoubleValue:progress];
        NSLog(@"progress: %f total+ %lld, done %lld", progress,_g_total_to_do,  _g_amount_done);
        if(progress < 100.0){
            return;
        }
    }
    [timer invalidate];
    idle = TRUE;
}


@end
