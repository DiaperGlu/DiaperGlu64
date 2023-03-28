//
//  DiaperGluLifeAppDelegate.m
//  DiaperGluLifeApplication
//
//  Created by James Norris on 4/3/18.
//  Copyright (c) 2018 James Norris. All rights reserved.
//

#import "DiaperGluLifeApplication.h"

@implementation DiaperGluLifeAppDelegate

- (void)sendDoLifeMessage
{
    // printf("doing sendDoLifeMessage\n");
    
    NSPoint mypoint;
    mypoint.x = 0;
    mypoint.y = 0;
    
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    
    if (myApp.lifepending != false)
    {
        return;
    }
    
    // if (myApp.islifing == false)
    // {
    //    return;
    // }
    
    // DiaperGluLifeAppDelegate* myAppDelegate = [self delegate];
    id myappWindow = [self window];
    
    id myevent = [NSEvent
        otherEventWithType: NSApplicationDefined
        location: mypoint
        modifierFlags: 0
        timestamp: 0
        windowNumber: [myappWindow windowNumber]
        context: 0
        subtype: 0
        data1: 0
        data2: 0];
    
    myApp.lifepending = true;
    
    [myApp postEvent: myevent atStart: false];
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSRect mainDisplayRect = [[NSScreen mainScreen] frame];
    
    id myappWindow = [self window];
    
    // [myappWindow setLevel:NSMainMenuWindowLevel+1];
    
    [myappWindow setOpaque: 1];
    
    [myappWindow setFrame: mainDisplayRect display: true];
    
    [myappWindow makeKeyAndOrderFront:self];
    
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    
    myApp.myAppDelegate = self;
    
    [myApp initLife];
    
    myApp.islifing = false;
    
    [self sendDoLifeMessage];
}


- (void)openDocument:(NSEvent *)theEvent
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp loadBitmap];
}

/*
- (void)saveDocument:(NSEvent *)theEvent
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp saveBitmap];
}
*/

- (void)saveDocumentAs:(NSEvent *)theEvent
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp saveBitmap];
}


@end
