//
//  TestViewController.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ProgressBarViewController : NSWindowController
@property(retain, nonatomic)IBOutlet NSProgressIndicator *progressIndicator;
@property (retain, nonatomic) IBOutlet NSButton *cancelButton;
-(IBAction)cancelButton:(id)sender;

@end

