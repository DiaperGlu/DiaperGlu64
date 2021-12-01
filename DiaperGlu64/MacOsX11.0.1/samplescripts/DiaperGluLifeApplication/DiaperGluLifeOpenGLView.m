//
//  DiaperGluLifeOpenGLView.m
//  DiaperGluLifeApplication
//
//  Created by James Norris on 4/3/18.
//  Copyright (c) 2018 James Norris. All rights reserved.
//

#import "DiaperGluLifeApplication.h"

@implementation DiaperGluLifeOpenGLView

- (IBAction) doCursorUp: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp cursorUp];
}

- (IBAction) doCursorDown: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp cursorDown];
}

- (IBAction) doCursorLeft: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp cursorLeft];
}

- (IBAction) doCursorRight: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp cursorRight];
}

- (IBAction) doDrawAtCursor: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp drawlifeformatcursor];
    
    /*
    switch(myApp.cursormode)
    {
        case 0:
            [myApp clearatcursor];
            break;
        case 1:
            [myApp setatcursor];
            break;
        case 2:
            [myApp toggleatcursor];
            break;
        default:
            break;
    }
    */
}

- (IBAction) doToggleCursor: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp toggleatcursor];
}

- (IBAction) cursorDrawsADot: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformdot;
    myApp.cursorw = lifeformdotw;
    myApp.cursorh = lifeformdoth;
}

- (IBAction) cursorDrawsABar3: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformblinker;
    myApp.cursorw = lifeformblinkerw;
    myApp.cursorh = lifeformblinkerh;
}

- (IBAction) cursorDrawsAToad: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformtoad;
    myApp.cursorw = lifeformtoadw;
    myApp.cursorh = lifeformtoadh; 
}

- (IBAction) cursorDrawsABeacon: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformbeacon;
    myApp.cursorw = lifeformbeaconw;
    myApp.cursorh = lifeformbeaconh;
}

- (IBAction) cursorDrawsAGlider5: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformglider;
    myApp.cursorw = lifeformgliderw;
    myApp.cursorh = lifeformgliderh;
}

- (IBAction) cursorDrawsASmallSpaceship: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformsmallspaceship;
    myApp.cursorw = lifeformsmallspaceshipw;
    myApp.cursorh = lifeformsmallspaceshiph;
}

- (IBAction) cursorDrawsACopperhead: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformcopperhead;
    myApp.cursorw = lifeformcopperheadw;
    myApp.cursorh = lifeformcopperheadh;
}

- (IBAction) cursorDrawsABlock4: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformblock4;
    myApp.cursorw = lifeformblock4w;
    myApp.cursorh = lifeformblock4h;
}

- (IBAction) cursorDrawsABeehive: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformbeehive;
    myApp.cursorw = lifeformbeehivew;
    myApp.cursorh = lifeformbeehiveh; 
}

- (IBAction) cursorDrawsABread: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformbread;
    myApp.cursorw = lifeformbreadw;
    myApp.cursorh = lifeformbreadh; 
}

- (IBAction) cursorDrawsABoat: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformboat;
    myApp.cursorw = lifeformboatw;
    myApp.cursorh = lifeformboath;
}

- (IBAction) cursorDrawsATub: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformtub;
    myApp.cursorw = lifeformtubw;
    myApp.cursorh = lifeformtubh;
}

- (IBAction) cursorDrawsALadder: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformladder;
    myApp.cursorw = lifeformladderw;
    myApp.cursorh = lifeformladderh;
}

- (IBAction) cursorDrawsAnAcorn: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformacorn;
    myApp.cursorw = lifeformacornw;
    myApp.cursorh = lifeformacornh;
}

- (IBAction) cursorDrawsARPentomino: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformrpentamino;
    myApp.cursorw = lifeformrpentaminow;
    myApp.cursorh = lifeformrpentaminoh;
}

- (IBAction) cursorDrawsARabbits: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.pcursorlifeform = lifeformrabbits;
    myApp.cursorw = lifeformrabbitsw;
    myApp.cursorh = lifeformrabbitsh;
}

- (IBAction) lifeGo: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    DiaperGluLifeAppDelegate* myAppDelegate = myApp.myAppDelegate;
    
    myApp.islifing = true;
    myApp.fullspeed = false;
    
    [myAppDelegate sendDoLifeMessage];
}

- (IBAction) lifeStop: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    // DiaperGluLifeAppDelegate* myAppDelegate = myApp.myAppDelegate;
    
    myApp.islifing = false;
}

- (IBAction) lifeFastForward: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    DiaperGluLifeAppDelegate* myAppDelegate = myApp.myAppDelegate;
    
    myApp.islifing = true;
    myApp.fullspeed = true;
    
    [myAppDelegate sendDoLifeMessage];
}

- (IBAction) lifeSingleStep: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    DiaperGluLifeAppDelegate* myAppDelegate = myApp.myAppDelegate;
    
    myApp.islifing = false;
    myApp.fullspeed = false;
    myApp.islifingonce = true;
    
    [myAppDelegate sendDoLifeMessage];
}

- (IBAction) cursorDrawModeClear: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.cursormode = 0;
    myApp.CursorDrawFunction = myApp.AreaNotSourceAnd;
}

- (IBAction) cursorDrawModeSet: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.cursormode = 1;
    myApp.CursorDrawFunction = myApp.AreaOr;
}

- (IBAction) cursorDrawModeToggle: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    myApp.cursormode = 2;
    myApp.CursorDrawFunction = myApp.AreaXor;
}

- (IBAction) doClearBitmap: (id)sender
{
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    [myApp clearBitmap];
}

- (void)mouseDown:(NSEvent *)theEvent {
    
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    // DiaperGluLifeAppDelegate* myAppDelegate = myApp.myAppDelegate;
    
    NSPoint event_location = [theEvent locationInWindow];
    
    NSPoint local_point = [self convertPoint:event_location fromView: self];
    
    if ((0 < local_point.x) &&
        (local_point.y < myApp.bitmapwidth) &&
        (0 < local_point.y) &&
        (local_point.y < myApp.bitmapheight)
        )
    {
        myApp.cursorx = (uint32_t)local_point.x;
        myApp.cursory = (uint32_t)local_point.y;
    }
    
    [self setNeedsDisplay:YES];
}

- (void)doLifeOnce
{
    uint64 x;
    
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    
    if (myApp.initwassuccessful == false) { return; }
    
    if (myApp.islifingonce != true)
    {
        if (myApp.islifing == false)
        {
            return;
        }
    }
    
    myApp.islifingonce = false;
    
    // printf("ppreviousrowneighbors = %llx\n", (uint64)myApp.ppreviousrowneighbors);
    // printf("pthisrowneighbors = %llx\n", (uint64)myApp.pthisrowneighbors);
    // printf("pnextrownneighbors = %llx\n", (uint64)myApp.pnextrownneighbors);
    // printf("pbitmapbuffer = %llx\n", (uint64)myApp.pbitmapbuffer);
    // printf("ptoprowneighbors = %llx\n", (uint64)myApp.ptoprowneighbors);
    
    
    x = myApp.LifeBitMapOnce (
        (uint64)myApp.ppreviousrowneighbors,
        (uint64)myApp.pthisrowneighbors,
        (uint64)myApp.pnextrownneighbors,
        myApp.bitmapwidth, // myscreenwidth,
        myApp.bitmapheight, // myscreenheight,
        (uint64)myApp.pbitmapbuffer,
        myApp.logicfunction, // logicfunction, 11100000
        (uint64)myApp.ptoprowneighbors);
    
    
    /*
    x = dg_lifeBitMapOnce (
        (unsigned char*)myApp.ppreviousrowneighbors,
        (unsigned char*)myApp.pthisrowneighbors,
        (unsigned char*)myApp.pnextrownneighbors,
        myApp.bitmapwidth, // myscreenwidth,
        myApp.bitmapheight, // myscreenheight,
        (unsigned char*)myApp.pbitmapbuffer,
        myApp.logicfunction, // logicfunction, 11100000
        (unsigned char*)myApp.ptoprowneighbors);
    */
    
    // printf("done lifing once, got return value of %llx\n", x);
    
}

- (void)drawRect:(NSRect)dirtyRect
{
    
    // Float32 x, y;
    
    // printf("doing drawRect:\n");
    //const unsigned char pcursorbitmap[1] = {0xff};
    
    DiaperGluLifeApplication* myApp = (DiaperGluLifeApplication*)[NSApplication sharedApplication];
    DiaperGluLifeAppDelegate* myAppDelegate = myApp.myAppDelegate;
    
    if (myApp.initwassuccessful == false)
    {
        //[myApp changeWindowsItem: myAppDelegate.window
        //    title: mycouldnotinitstring
        //    filename:false];
        [myAppDelegate.window setTitle:@"Could not initialize. You probably have to edit mylocalpath in DiaperGluLifeApplication.m"];
    }
    
    [super drawRect:dirtyRect];
    
    // CGContextRef myContext = [[NSGraphicsContext currentContext] graphicsPort];
    
   // ********** Your drawing code here ********** // 2
/*
    CGRect myScreenRect = {
        0, // x
        0, // y
        myApp.bitmapwidth, // w
        myApp.bitmapheight}; // h
    */
    myApp.myView = self;
    
    // Drawing code here.
    
    if (myApp.initwassuccessful == false)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        return;
    }
    
    
    if (myApp.pbitmapbuffer != 0)
    {
        /*
        myApp.bitmapToPixels (
            (uint64)myApp.ppixelbuffer1,            // rdi
            (uint64)myApp.pbitmapbuffer,             // rsi
            0, // clearpixelvalue,       // rdx
            (myApp.bitmapwidth * myApp.bitmapheight) / 8,//  bitmapsizeinuint8s,    // rcx
            0xFFFFFFFF); // setpixelvalue)
        
        
        myApp.myBitMapImageRef = CGImageCreate(
            myApp.bitmapwidth,
            myApp.bitmapheight,
            8, // bitsPerComponent,
            32, // bitsPerPixel,
            myApp.bitmapwidth * 4, // bytesPerRow,
            myApp.myBaseColorSpace,
            0, // bitMapInfo,
            myApp.myPixelBufferDataProvider,
            NULL, // pdecode, NULL means don't allow remapping of color values
            false, // fshouldinterpolate,
            0); // color rendering intent.. 0 means default intent);
        
        CGContextDrawImage(
            myContext,
            myScreenRect,
            myApp.myBitMapImageRef);
        
        */
        /*
        myApp.myBitMapImageMaskRef = CGImageMaskCreate(
            myApp.bitmapwidth,
            myApp.bitmapheight,
            1, // bitsPerComponent,
            1, // size_t bitsPerPixel,
            myApp.bitmapwidth / 8, // bytesPerRow,
            myApp.myBitMapDataProvider,
            NULL, // const CGFloat *decode,
            false); // shouldInterpolate);
        */
        /*
        myApp.myBitMapImageRef = CGImageCreate(
            myApp.bitmapwidth,
            myApp.bitmapheight,
            1, // bitsPerComponent,
            1, // bitsPerPixel,
            myApp.bitmapwidth / 8, // bytesPerRow,
            myApp.myColorSpace,
            0, // bitMapInfo,
            myApp.myBitMapDataProvider,
            NULL, // pdecode, NULL means don't allow remapping of color values
            false, // fshouldinterpolate,
            0); // color rendering intent.. 0 means default intent);
        */
        /*
        CGContextDrawImage(
            myContext,
            myScreenRect,
            myApp.myBitMapImageMaskRef);
        */
        
        glViewport(0, 0, (GLfloat)myApp.bitmapwidth, (GLfloat)myApp.bitmapheight);
        
        // the order of these instructions is important... otherwise color gets messed up
        glClear(GL_COLOR_BUFFER_BIT); // the clear is needed because glBitmap does not draw the zeroes.
        
        // You can specify this in window coordinates now
        
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2d(-1.0, -1.0);
        
        // printf("  doing glBitmap\n");
        
        glBitmap(
            (int)myApp.bitmapwidth,
            (int)myApp.bitmapheight,
            0.0,
            0.0,
            0.0,
            0.0,
            (const unsigned char*)myApp.pbitmapbuffer); // doesn't draw lower right pixel
        
        if (myApp.fullspeed == false)
        {
            [myAppDelegate sendDoLifeMessage];
        }
        

        if (myApp.fullspeed == false)
        {
            [myAppDelegate sendDoLifeMessage];
        }
        
    }
    
    // draw the cursor
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2d(
        (myApp.cursorx * (2.0/myApp.bitmapwidth)) - 1.0,
        (myApp.cursory * (2.0/myApp.bitmapheight)) - 1.0);
    
    glBitmap(
            (int)myApp.cursorw,
            (int)myApp.cursorh,
            0.0,
            0.0,
            0.0,
            0.0,
            (const unsigned char*)myApp.pcursorlifeform);
    
    
    /*
    glBegin(GL_POINTS);
    
    {
        x = ((Float32)myApp.cursorx)/((Float32)(myApp.bitmapwidth - 1));
        y = ((Float32)myApp.cursory)/((Float32)(myApp.bitmapheight - 1));
        
        x = (x * 2) - 1;
        y = (y * 2) - 1;
        
        glVertex2f((GLfloat)x, (GLfloat)y);
    }
    
    glEnd();
 
    */
     
    glFlush();
}

@end
