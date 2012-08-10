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
#import "Utils.h"
#import "ProgressBarViewController.h"
#import "MessageUtils.h"
#import "EncryptionOptions.h"

extern long long _g_total_to_do;
extern long long _g_amount_done;


@implementation AppDelegate

@synthesize window = _window;
@synthesize password, rePassword, filePath, encryptButton, dencryptButton, rePasswordLable, securityLable, msgLable, securityOption;
@synthesize  status, progressBarViewController, idle, viewMoment, keepEncryptedFile, keepUnencryptedFile ;


-(void)applicationWillFinishLaunching:(NSNotification *)notification
{
    [_window setFrame:CGRectMake([_window frame].origin.x, [_window frame].origin.y, [_window frame].size.width, 250)  display:YES animate:YES];
    viewMoment = SMALL_VIEW;
    idle = TRUE;
    srand((unsigned int)time(NULL));

}

/**
 * Code to be executed if a ".myfsec" file is double clicked!
 */
-(BOOL)application:(NSApplication *)app openFile:(NSString *)filename
{
    if(!idle){
        NSAlert * alert = [NSAlert alertWithMessageText:[ MessageUtils getEncodeMessage:ERROR_APPLICATION_BUSSY] defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""   ];
        [alert setAlertStyle:NSInformationalAlertStyle];
        [alert runModal];
    }else{
    
        [filePath setStringValue:filename];
        [self setWindowToTypeOfFile];
        NSLog(@"File name %@", filename);
    }
    return YES;
}

/**
 *  Code executed when the progress bar should not be shown any more
 */

- (void)sheetDidEnd:(NSWindow *)sheet
         returnCode:(int)returnCode
        contextInfo:(void  *)contextInfo
{
    [[NSApplication sharedApplication] stopModal];
    [progressBarViewController.window orderOut:nil];
    [self showStatusMsg];

}

/**
 * 
 */
-(int) commonChecks
{
    if([[password stringValue] length] == 0)
    {
        return ERROR_PASSWORD;
    }
    if([[filePath stringValue] length] == 0)
    {
        return ERROR_CHOOSE_A_FILE;
    }
    return OK;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    idle = TRUE;
    //Service Provider declaration and update of system services
    [NSApp setServicesProvider: self];
    NSUpdateDynamicServices();

}

-(void) resetForm
{
    if(viewMoment == BIG_VIEW){
        [_window setFrame:CGRectMake([_window frame].origin.x, [_window frame].origin.y+140, [_window frame].size.width, 250)  display:YES animate:YES];
        viewMoment = SMALL_VIEW;
    }
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
    [self.keepUnencryptedFile setHidden:YES];
    [self.keepEncryptedFile setHidden:YES];
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
    NSString *fileName = [filePath stringValue];
    int fileType, securityType;
    fileType = [Encryptor checkIfFileIsOurs:fileName];
    [self.msgLable setStringValue:@""];
    [self.rePasswordLable setHidden:YES];
    [self.rePassword setHidden:YES];
    [self.securityLable setHidden:YES];
    [self.securityOption setHidden:YES];
    [self.keepUnencryptedFile setHidden:YES];
    [self.keepEncryptedFile setHidden:YES];
    [_window makeFirstResponder:password];
    
    if(fileType == ERROR_FILE_DOES_NOT_EXIST)
    {
        if(viewMoment == BIG_VIEW){
            [_window setFrame:CGRectMake([_window frame].origin.x, [_window frame].origin.y+140, [_window frame].size.width, 250)  display:YES animate:YES];
            viewMoment = SMALL_VIEW;
        }
        [msgLable setStringValue:ERROR_FILE_DOES_NOT_EXIST_MSG];
        [self.encryptButton setEnabled:NO];
        [self.dencryptButton setEnabled:NO];

        //TODO: IF FILE DOES NOT EXIST
    }else if( fileType == ERROR_NOT_SUPPORTED)
    {   
        if(viewMoment == SMALL_VIEW){
            [_window setFrame:CGRectMake([_window frame].origin.x, [_window frame].origin.y-140 , [_window frame].size.width, 390)  display:YES animate:YES];
            viewMoment = BIG_VIEW;
        }
        [self.encryptButton setEnabled:YES];
        [self.dencryptButton setHidden:YES];
        [self.encryptButton setHidden:NO];
        [self.rePasswordLable setHidden:NO];
        [self.rePassword setHidden:NO];
        [self.securityLable setHidden:NO];
        [self.securityOption setHidden:NO];
        securityType = [self getSecurityType:[self.securityOption selectedTag]];
        if(securityType == SECURITY_TYPE_AES256)
        {
            [self.keepUnencryptedFile setHidden:NO];
        }
    }else if( fileType == SECURITY_TYPE_QUICKENCODE || fileType == SECURITY_TYPE_AES256 )
    {
        if(viewMoment ==BIG_VIEW){
            [_window setFrame:CGRectMake([_window frame].origin.x, [_window frame].origin.y+140, [_window frame].size.width, 250)  display:YES animate:YES];
            viewMoment = SMALL_VIEW;
        }
        [encryptButton setHidden:YES];
        [dencryptButton setEnabled:YES];
        [dencryptButton setHidden:NO];
        [self.rePasswordLable setHidden:YES];
        [self.rePassword setHidden:YES];

        if(fileType == SECURITY_TYPE_AES256)
        {
            [self.keepEncryptedFile setHidden:NO];
        }
        //TODO: FILE TO DENCRYPT
    }else{
        //UNKNOW ERROR
    }
    
}
-(IBAction)pathFileFilled:(id)sender
{
    [self setWindowToTypeOfFile];
}

 /*
  * -(void) finishingTask
  * Code that has to be executed after a file has already been encrypted/decrypted
  * For now: remove the modal panel with the progress bar
  *
  */
-(void) finishingTask
{
    [[NSApplication sharedApplication] endSheet:progressBarViewController.window];
    [[NSApplication sharedApplication] stopModal];
    [progressBarViewController.window orderOut:nil];
    [progressBarViewController.window close];
}

/**
 * -(void) encode:(NSTimer*) timer
 *  Call this function to perform the encode of a file, this is ment to be 
 *  called in a different thread. This will start timer, ecnrypt file and 
 *  stop timer and remove progress bar
 *  timer: Timer setted up buy caller to perform a progress status bar.
 *
 */

-(void)encode:(NSTimer *) timer{
    
    if(timer == nil){
        status = ERROR_UNKNOWN;
        return;
    }
    
    long option = [securityOption selectedTag];
    [timer fire];
    NSMutableDictionary * options = [[ NSMutableDictionary alloc] init];
    [options setValue:[NSNumber numberWithInt:[self getSecurityType:option]] forKey:OPTION_SECURITY];
    status =[Encryptor encodeDispacher:filePath.stringValue password:password.stringValue options:options];

    [timer invalidate];
    [self performSelectorOnMainThread:@selector(finishingTask) withObject:nil waitUntilDone:YES];
    idle = TRUE;
  

}
/**
 *  Action of the encryt button
 */
-(IBAction)encryptButtonPushed:(id)sender
{
      status = 0;
    idle= FALSE;
    long option = [securityOption selectedTag];
    NSLog(@"option is: %ld", option);
    if( (status = [self commonChecks]) != OK)
    {
        [self showStatusMsg];
    }    else if([[password stringValue] compare:[rePassword stringValue]] != 0)
    {
        status = ERROR_PASSWORDS_DONT_MATCH;
        [self showStatusMsg];
        idle = TRUE;
        return;

    }else{
        NSTimer *timer;
        
        timer = [NSTimer scheduledTimerWithTimeInterval:0.5 
                                                 target:self selector:@selector(progresIndicatorUpdater:) 
                                               userInfo:nil repeats:YES] ;

        [self performSelectorInBackground:@selector(encode:) withObject:timer];
        progressBarViewController = [[ProgressBarViewController alloc] initWithWindowNibName:@"ProgressPanel"];
        [[NSApplication sharedApplication] beginSheet: progressBarViewController.window
                                       modalForWindow: _window
                                        modalDelegate: self
                                       didEndSelector: @selector(sheetDidEnd:returnCode:contextInfo:)
                                          contextInfo: nil];
        
    }
    
  
    
}
/**
 * -(void) decode:(NSTimer*) timer
 *  Call this function to perform the decode of a file, this is ment to be 
 *  called in a different thread. This will start timer, decrypt file and 
 *  stop timer and remove progress bar
 *  timer: Timer setted up buy caller to perform a progress status bar.
 *
 */

-(void)decode:(NSTimer*) timer
{
 
    if(timer == nil){
        status = ERROR_UNKNOWN;
        return;
    }
    [timer fire];

    status =[Encryptor decodeDispacher:filePath.stringValue password:password.stringValue options:nil ];
    [timer invalidate];
    [self performSelectorOnMainThread:@selector(finishingTask) withObject:nil waitUntilDone:YES];
    idle = TRUE;

}
/*
 *  Action of the decrypt button
 */
-(IBAction)dencryptButtonPushed:(id)sender
{

    status = 0;
    idle = FALSE;
    if(viewMoment == BIG_VIEW)
        return ;

    if( (status = [self commonChecks]) != OK)
    {
        [self showStatusMsg];
    }else{
        // IF no errors, setup timer, to start and decode async!
        NSTimer *timer;
        
        timer = [NSTimer scheduledTimerWithTimeInterval:0.5 
                                                 target:self selector:@selector(progresIndicatorUpdater:) 
                                               userInfo:nil repeats:YES] ;
        

        [self performSelectorInBackground:@selector(decode:) withObject:timer];
        // show the progres bar in a diferent panel
        progressBarViewController = [[ProgressBarViewController alloc] initWithWindowNibName:@"ProgressPanel"];
        [[NSApplication sharedApplication] beginSheet: progressBarViewController.window
                                       modalForWindow: _window
                                        modalDelegate: self
                                       didEndSelector: @selector(sheetDidEnd:returnCode:contextInfo:)
                                          contextInfo: nil];
    }
  

}

-(IBAction)chooseFileButtonPushed:(id)sender
{
    
    NSOpenPanel *openDlg = [NSOpenPanel openPanel];
    [_window makeFirstResponder:filePath];

    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];
    // Disable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];

    [_window makeKeyAndOrderFront:openDlg];
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
    NSAlert * alert = [NSAlert alertWithMessageText:[MessageUtils getEncodeMessage:status] defaultButton:nil alternateButton:nil otherButton:nil informativeTextWithFormat:@""   ];
    [alert setAlertStyle:NSInformationalAlertStyle];
    [alert beginSheetModalForWindow:_window modalDelegate:self didEndSelector:@selector(alertDidEnd:returnCode:contextInfo:) contextInfo:nil];
    [_window makeKeyAndOrderFront:alert];
}

-(IBAction)securityLevelChosen:(id)sender
{
    long securityType = [self getSecurityType:[self.securityOption selectedTag]];
    if(securityType == SECURITY_TYPE_AES256)
    {
        [self.keepUnencryptedFile setHidden:NO];
    }else{
        [self.keepUnencryptedFile setHidden:YES];
    }
}



-(void)progresIndicatorUpdater:(NSTimer *)timer { 
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
}


@end
