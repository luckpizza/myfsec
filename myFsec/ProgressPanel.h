//
//  ProgressPanel.h
//  myFsec
//
//  Created by Lucas Pizzagalli on 5/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <AppKit/AppKit.h>

@interface ProgressPanel : NSPanel
@property (retain, nonatomic) IBOutlet NSProgressIndicator * progressIndicator;
@property (retain, nonatomic) IBOutlet NSWindow * window;

@end
