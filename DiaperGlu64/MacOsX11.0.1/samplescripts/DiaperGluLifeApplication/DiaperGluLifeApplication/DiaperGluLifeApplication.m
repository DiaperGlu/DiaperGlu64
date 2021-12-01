//
//  DiaperGluLifeApplication.m
//  DiaperGluLifeApplication
//
//  Created by James Norris on 4/8/18.
//  Copyright (c) 2018 James Norris. All rights reserved.
//

#import "DiaperGluLifeApplication.h"
// #import "DiaperGluLifeOpenGLView.h"
// #import "DiaperGluLifeAppDelegate.h"
// #import <stdio.h>



@implementation DiaperGluLifeApplication

// sorry about this :-)
// edit this to point to where diaperglu is installed
//  this demo assumes libdiaperglu.dylib is at the mylocalpath place
//  and this demo assumes some support files are in the samplescripts subdirectory
//  and this demo assumes the DiaperGluLifeApplication demo is in the samplescripts subdirectory
NSString* mylocalpath = @"/Users/jamespatricknorris/desktop/DiaperGlu64/macosx10.15.6/";

unsigned char bittbl[8] = {0x80, 0x40, 0x20, 0x10, 8, 4, 2, 1};

- (void)saveBitmap
{
    NSSavePanel* pmysavepanel = [NSSavePanel savePanel];
 
    [pmysavepanel beginWithCompletionHandler:^(NSInteger result)
    {
        if (result == NSFileHandlingPanelOKButton)
        {
            char myfilenamebuf[1024];
                    
            int myfileid = -1;
            int flag = -1;
                    
            NSURL*  theDoc = [pmysavepanel URL];
                    
            [theDoc getFileSystemRepresentation: myfilenamebuf maxLength: 1023];
                    
            myfileid = open(
                //"/Users/jim/Desktop/mybitmap.bin",
                myfilenamebuf,
                // O_CREAT | O_TRUNC | O_WRONLY);
                O_CREAT | O_TRUNC | O_RDWR);
            
            if (-1 != myfileid)
            {
                flag = fchmod(myfileid, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
                
                if (self.pbitmapbuffer != 0)
                {
                    write(myfileid, (const void *)self.pbitmapbuffer, self.bitmapsize);
                }
                
                fsync(myfileid);
            
                close(myfileid);
            }
        }
    }];
    
    // don't really need to redisplay on a save
    // [self.myView setNeedsDisplay: true];
}

- (void) clearBitmap // slow way to do this
{
    uint64 i;
    if (self.pbitmapbuffer == 0)
    {
        return;
    }
    
    for (i = 0; i < self.bitmapsize; i++)
    {
        self.pbitmapbuffer[i] = 0;
    }
}

- (void) loadBitmap
{
    NSOpenPanel* pmyopenpanel = [NSOpenPanel openPanel];
            
    [pmyopenpanel setCanChooseFiles: true];
    [pmyopenpanel setCanChooseDirectories: true];
    [pmyopenpanel setResolvesAliases: true];
 
    [pmyopenpanel beginWithCompletionHandler:^(NSInteger result)
    {
        if (result == NSFileHandlingPanelOKButton) {
                
            char myfilenamebuf[1024];
            struct stat mystat;
                    
            myfilenamebuf[0] = 0; // manually putting in nul terminator just in case
                    
            NSURL*  theDoc = [[pmyopenpanel URLs] objectAtIndex:0];
                    
            [theDoc getFileSystemRepresentation: myfilenamebuf maxLength: 1023];
                    
            // Open  the document.
            int myopenfileid = open(
                //"/Users/jim/Desktop/mybitmap.bin",
                myfilenamebuf,
                // O_RDONLY);
                O_RDWR);
            
            if (-1 != myopenfileid)
            {
                fstat(myopenfileid, &mystat);
                        
                if (mystat.st_size != self.bitmapsize)
                {
                    printf("bitmapsize = %llx\n", self.bitmapsize);
                    printf("filesize = %llx\n", mystat.st_size);
                    
                    NSAlert *alert = [[NSAlert alloc] init];
                    [alert addButtonWithTitle:@"OK"];
                    [alert setInformativeText: @"File is the wrong length. It's probably not a bitmap."];
                    [alert setAlertStyle:NSWarningAlertStyle];
                    
                    [alert runModal];
                          
                    // [alert release];
                }
                else
                {
                    if (self.pbitmapbuffer != 0)
                    {
                        read(myopenfileid, (void *)self.pbitmapbuffer, self.bitmapsize);
                    }
                }
            
                close(myopenfileid);
            }
            else
            {
                NSAlert *alert = [[NSAlert alloc] init];
                NSString *myalertstring = [NSString init];
                myalertstring = [myalertstring initWithCString: myfilenamebuf encoding: NSASCIIStringEncoding];
                [alert addButtonWithTitle:@"Could not open file!"];
                [alert setInformativeText: myalertstring];
                [alert setAlertStyle:NSWarningAlertStyle];
                    
                [alert runModal];
                // [alert release];
            }
        }
    }];
    
    [self.myView setNeedsDisplay: true];
}

- (uint64) xytooffset
{
    uint64 offset;
    if (self.cursorx >= self.bitmapwidth)
    {
        return (0);
    }
    
    if (self.cursory>= self.bitmapheight)
    {
        return (0);
    }
    
    offset = (self.cursorx + (self.bitmapwidth * self.cursory))/8;
    return (offset);
}

- (void) setatcursor
{
    if (self.pbitmapbuffer == 0) { return; }
    uint64 offset = [self xytooffset];
    uint64 bittblindex = self.cursorx & 7;
    
    self.pbitmapbuffer[offset] =
        self.pbitmapbuffer[offset] | bittbl[bittblindex];
    
    [self.myView setNeedsDisplay: true];
}

- (void) clearatcursor
{
    if (self.pbitmapbuffer == 0) { return; }
    uint64 offset = [self xytooffset];
    uint64 bittblindex = self.cursorx & 7;
    
    self.pbitmapbuffer[offset] =
        self.pbitmapbuffer[offset] & (0xff ^ bittbl[bittblindex]);
    
    [self.myView setNeedsDisplay: true];
}

- (void) toggleatcursor
{
    if (self.pbitmapbuffer == 0) { return; }
    uint64 offset = [self xytooffset];
    uint64 bittblindex = self.cursorx & 7;
    
    self.pbitmapbuffer[offset] =
        self.pbitmapbuffer[offset] ^ bittbl[bittblindex];
    
    [self.myView setNeedsDisplay: true];
}

- (void) drawlifeformatcursor
{
    if (self.pbitmapbuffer == 0) { return; }
    [self AreaXorWithWrapUsingPdest:
                              (uint64)self.pbitmapbuffer
            Psrc:             (uint64)self.pcursorlifeform
            DestWidthInBits:  (self.bitmapwidth)
            DestHeightInBits: self.bitmapheight
            SrcWidthInBits:   self.cursorw
            SrcHeightInBits:  self.cursorh
            DestXInBits:      self.cursorx
            DestYInBits:      self.cursory];
}

- (void) cursorUp
{
    self.cursory++;
    if (self.cursory >= self.bitmapheight)
    {
        self.cursory = 0;
    }
    
    [self.myView setNeedsDisplay: true];
}

- (void) cursorDown
{
    if (self.cursory == 0)
    {
        self.cursory = self.bitmapheight - 1;
    }
    else
    {
        self.cursory--;
    }
    
    [self.myView setNeedsDisplay: true];
}

- (void) cursorRight
{
    self.cursorx++;
    if (self.cursorx >= self.bitmapwidth)
    {
        self.cursorx = 0;
    }
    
    [self.myView setNeedsDisplay: true];
}

- (void) cursorLeft
{
    if (self.cursorx == 0)
    {
        self.cursorx = self.bitmapwidth - 1;
    }
    else
    {
        self.cursorx--;
    }
    
    [self.myView setNeedsDisplay: true];
}

- (void) sendEvent: (NSEvent*) myevent
{
    uint64 mytype = [myevent type];
    DiaperGluLifeAppDelegate* myAppDelegate = self.myAppDelegate;
    DiaperGluLifeOpenGLView* myView = self.myView;
    
    if (mytype == NSApplicationDefined)
    {
        if (self.pbitmapbuffer == 0) { return; }
        self.lifepending = false;
        
        [myView doLifeOnce];
        
        if (self.fullspeed != false)
        {
            [myAppDelegate sendDoLifeMessage];
            if (self.frameskip == 1)
            {
               [myView setNeedsDisplay: true];
               self.frameskip = 0;
            }
            else
            {
               self.frameskip++;
            }
        }
        else
        {
            [myView setNeedsDisplay: true];
        }
    }
    else
    {
        [super sendEvent: myevent];
    }
}
/*
- (void) initNeighborsForEightCellsTable
{
    uint32 i, j;
    
    if (self.pbitmapbuffer == 0) { return; }
    
    for (i = 0; i < 0x100; i++)
    {
        for (j = 0; j < (self.bitmapwidth + 2); j++)
        {
            self.pthisrowneighbors[j] = 0;
            self.ppreviousrowneighbors[j] = 0;
        }
        
        self.pbitmapbuffer[1] = (unsigned char)i;
        
        self.CalcNeighborsForRow(
                (uint64)self.pbitmapbuffer, // prowbits,
                (uint64)self.pthisrowneighbors,
                (uint64)self.pnextrownneighbors,
                1, // dwordsperrow,
                (uint64)self.self.pthisrowneighbors + 64, // pthisrownneighborsend,
                (uint64)self.pnextrownneighbors + 64); // pnextrownneighborsend)
        
        for (j=0; j < 10; j++)
        {
            self.pthisneighborsforeightcellstable[(i*0x10) + j] = self.pthisrowneighbors[j+7];
            self.pnextneighborsforeightcellstable[(i*0x10) + j] = self.pnextrownneighbors[j+7];
        }
    }
}
*/
- (void) initLife
{
    self.initwassuccessful = false;
    self.fullspeed = false;
    self.islifing = false;
    self.islifingonce = false;
    
    self.bitmapwidth = 1280;
    self.bitmapheight = 752;
    self.logicfunction = 0xe0;
    
    self.frameskip = 0;
    
    self.bitmapsize = (self.bitmapwidth * self.bitmapheight)/8;
    self.pixelbuffersize = (self.bitmapwidth * self.bitmapheight) * 4;
    
    char **myfakevars = 0;
    // uint64 mysymbollisthlistid;
    uint64 i,x;
    // uint64 plifecodebuffer;
    // uint64* plifecodebufferlength;
    uint64 pgamedevbitmapbuffer;
    uint64* pgamedevbitmapbufferlength;
    uint64 gamedevbitmapbufferlength;
    uint64 bitmappadding = 16;
    
    // const char libdiaperglupathfilename[] = "/Users/jim/desktop/DiaperGlu64/macosx10.9.5/libdiaperglu.dylib";
    // const char lifedglibpathfilename[]    = "/Users/jim/desktop/DiaperGlu64/macosx10.9.5/samplescripts/life.dglib";
    // const char lifeglulistpathfilename[]  = "/Users/jim/desktop/DiaperGlu64/macosx10.9.5/samplescripts/life.glulist";
    // const char clevelandgamedevsbitmapfilename[] = "/Users/jim/desktop/DiaperGlu64/macosx10.9.5/samplescripts/DiaperGluLifeApplication/DiaperGluLifeApplication/clevelandgamedevs.rawbmp";
    
    NSString* mylibdiaperglupathfilename = [mylocalpath stringByAppendingString: @"libdiaperglu.dylib"];
    NSString* myliblifepathfilename = [mylocalpath stringByAppendingString: @"samplescripts/lifedylib/liblife.dylib"];
    // NSString* mydg2dgraphicspathfilename = [mylocalpath stringByAppendingString: @"samplescripts/dg2dgraphicsdylib/libdg2dgraphics.dylib"];
    // NSString* mylifedglibpathfilename = [mylocalpath stringByAppendingString: @"samplescripts/lifenglulib/life.dglib"];
    // NSString* mylifeglulistpathfilename = [mylocalpath stringByAppendingString: @"samplescripts/life.glulist"];
    NSString* myclevelandgamedevsbitmapfilename = [mylocalpath stringByAppendingString: @"samplescripts/DiaperGluLifeApplication/DiaperGluLifeApplication/clevelandgamedevs.rawbmp"];
    
    // const char psymbollistname[]          = "lifesymbols";
    //    const char dg_getoverlapsegmentname[] = "dg_getoverlapsegment";
    // const char calcneighborsforrowname[]  = "CalcNeighborsForRow";
    //    const char UpdateCellsForRowname[]    = "UpdateCellsForRow";
    // const char ClearNeighborsname[]       = "ClearNeighbors";
    //    const char copyNeighborsname[]        = "copyNeighbors";
    //    const char MoveDwordsname[]           = "MoveDwords";
    //    const char CalcNeighborsForRowNname[] = "CalcNeighborsForRowN";
    //    const char UpdateCellsForRowNname[]   = "UpdateCellsForRowN";
    // const char LifeBitMapOncename[]             = "LifeBitMapOnce";
    // const char AreaXorname[]                    = "AreaXor";
    // const char AreaOrname[]                     = "AreaOr";
    // const char AreaNotSourceAndname[]           = "AreaNotSourceAnd";
    // const char bitmapToPixelsname[]             = "bitmapToPixels";
    // const char getWrapOffsetname[]              = "getOverlapOffset";
    // const char thisneighborsaddtblname[]        = "thisneighborsaddtbl";
    // const char nextneighborsaddtblname[]        = "nextneighborsaddtbl";
    
    self.ptoprowneighbors = malloc(self.bitmapwidth + 64); // need at least 2 extra
    self.ppreviousrowneighbors = malloc(self.bitmapwidth + 64);
    self.pthisrowneighbors = malloc(self.bitmapwidth + 64);
    self.pnextrownneighbors = malloc(self.bitmapwidth + 64);
    self.pbitmapbuffer = malloc(self.bitmapsize + bitmappadding);
    self.ppixelbuffer1 = malloc(self.pixelbuffersize + 64);
    // self.pthisneighborsforeightcellstable = malloc(0x1000); // 0x100 * 0x10
    // self.pnextneighborsforeightcellstable = malloc(0x1000); // 0x100 * 0x10
        
    self.hdiaperglulib = dlopen([mylibdiaperglupathfilename cStringUsingEncoding: NSASCIIStringEncoding], RTLD_LOCAL);
    self.hlifelib      = dlopen([myliblifepathfilename cStringUsingEncoding: NSASCIIStringEncoding], RTLD_LOCAL);
    // self.hdg2dgraphicslib = dlopen([mydg2dgraphicspathfilename cStringUsingEncoding: NSASCIIStringEncoding], RTLD_LOCAL);
        
    if (self.hdiaperglulib == 0)
    {
        // printf("could not open libdiaperglu\n");
        // myLabel.text = [NSString localizedStringWithFormat: @"%s", dlerror()];
        return;
    }
    
    if (self.hlifelib == 0)
    {
        // printf("could not open libdiaperglu\n");
        // myLabel.text = [NSString localizedStringWithFormat: @"%s", dlerror()];
        return;
    }
        
        self.dg_hsymbolnametovalue = dlsym(self.hdiaperglulib, "dg_hsymbolnametovalue");
        self.dg_getnamedsymbollisthideid = dlsym(self.hdiaperglulib, "dg_getnamedsymbollisthideid");
        self.dg_nglufile = dlsym(self.hdiaperglulib, "dg_nglufile");
        self.dg_loadfile = dlsym(self.hdiaperglulib, "dg_loadfile");
        self.dg_init = dlsym(self.hdiaperglulib, "dg_init");
        self.dg_getpbuffer = dlsym(self.hdiaperglulib, "dg_getpbuffer");
        self.dg_getpbufferoffset = dlsym(self.hdiaperglulib, "dg_getpbufferoffset");
        self.dg_geterrorcount = dlsym(self.hdiaperglulib, "dg_geterrorcount");
        self.dg_poperror = dlsym(self.hdiaperglulib, "dg_poperror");
        // self.dg_bswap = dlsym(self.hdiaperglulib, "dg_bswap");
        
        // self.CalcNeighborsForRow = dlsym(self.hlifelib, "dg_calcNeighborsForRow");
        self.LifeBitMapOnce = dlsym(self.hlifelib, "dg_lifeBitMapOnce");
        self.AreaOr = dlsym(self.hlifelib, "dg_areaOr");
        self.AreaXor = dlsym(self.hlifelib, "dg_areaXor");
        self.AreaNotSourceAnd = dlsym(self.hlifelib, "dg_areaNotSourceAnd");
        self.getWrapOffset = dlsym(self.hlifelib, "dg_getOverlapOffset");
        self.pthisneighborsforeightcellstable = dlsym(self.hlifelib, "dg_thisneighborsaddtbl");
        self.pnextneighborsforeightcellstable = dlsym(self.hlifelib, "dg_nextneighborsaddtbl");
        
        if ((uint64)self.dg_init == 0)
        {
            // printf("could not init Diaperglu\n");
            // myLabel.text = [NSString localizedStringWithFormat: @"%s", dlerror()];
            // return self;
            
            NSAlert *alert = [[NSAlert alloc] init];
            // NSString *myalertstring = [NSString init];
                // myalertstring = [myalertstring initWithCString: myfilenamebuf encoding: NSASCIIStringEncoding];
                [alert addButtonWithTitle:@"could not initialize Diaperglu."];
                // [alert setInformativeText: myalertstring];
                [alert setAlertStyle:NSWarningAlertStyle];
                    
                [alert runModal];
            
            return;
        }
        
        self.pBHarrayhead = self.dg_init(0, myfakevars);
        
        if (self.pBHarrayhead == (uint64)-1)
        {
            // myLabel.text = @"could not initialize pBHarrayhead";
            // return self;
        }
    
        self.gamedevbitmapbufferid = self.dg_loadfile(
            self.pBHarrayhead,
            (uint64)[myclevelandgamedevsbitmapfilename cStringUsingEncoding: NSASCIIStringEncoding],
            myclevelandgamedevsbitmapfilename.length);
        
        if (self.gamedevbitmapbufferid == (uint64)-1) // could ignore this error and leave bitmap empty
        {
            printf("could not load Clevland Game Dev bit map\n");
            // myLabel.text = [NSString localizedStringWithFormat:
             //   @"Could not load dglib. Top error = %s",
             //   (const char*)self.dg_poperror(self.pBHarrayhead)];
            return;
        }
    
        pgamedevbitmapbuffer = self.dg_getpbuffer (
            self.pBHarrayhead,
            self.gamedevbitmapbufferid,
            (uint64)&pgamedevbitmapbufferlength);
    
        gamedevbitmapbufferlength = *pgamedevbitmapbufferlength;
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            printf("Could not get pointer to Cleveland Game Dev bit map buffer\n");
            // myLabel.text = @"Could not get pointer to lifelib buffer.";
            // return self;
            return;
        }
        /*
        self.lifelibbufferid = self.dg_loadfile(
            self.pBHarrayhead,
            (uint64)[mylifedglibpathfilename cStringUsingEncoding: NSASCIIStringEncoding],
            mylifedglibpathfilename.length);
        
        if (self.lifelibbufferid == (uint64)-1)
        {
            // printf("could not load lifelib\n");
            // myLabel.text = [NSString localizedStringWithFormat:
             //   @"Could not load dglib. Top error = %s",
             //   (const char*)self.dg_poperror(self.pBHarrayhead)];
            return;
        }
        
        self.dg_nglufile(
            self.pBHarrayhead,
            (uint64)[mylifeglulistpathfilename cStringUsingEncoding: NSASCIIStringEncoding],
            mylifeglulistpathfilename.length);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("could not nglu life glulist\n");
            // myLabel.text = @"Could not nglu life glu file.";
            return;
        }
        
        self.lifesymbollistelementid = self.dg_getnamedsymbollisthideid (
            self.pBHarrayhead,
            (uint64)psymbollistname,
            sizeof(psymbollistname) - 1,
            (uint64)&mysymbollisthlistid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get symbol list hlist id and element id.";
            // return self;
        }
        
        self.lifesymbollisthlistid = mysymbollisthlistid;

        
        plifecodebuffer = self.dg_getpbuffer (
            self.pBHarrayhead,
            self.lifelibbufferid,
            (uint64)&plifecodebufferlength);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get pointer to lifelib buffer.";
            // return self;
        }
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)dg_getoverlapsegmentname,
            sizeof(dg_getoverlapsegmentname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get dg_getoverlapsegment symbol value.";
            // return self;
        }
        
        self.dg_getoverlapsegment = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)calcneighborsforrowname,
            sizeof(calcneighborsforrowname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get calcneighborsforrow symbol value.";
            // return self;
        }
        
        self.CalcNeighborsForRow = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)UpdateCellsForRowname,
            sizeof(UpdateCellsForRowname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get UpdateCellsForRow symbol value.";
            // return self;
        }
        
        self.UpdateCellsForRow = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)ClearNeighborsname,
            sizeof(ClearNeighborsname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get ClearNeighbors symbol value.";
            // return self;
        }
        
        self.ClearNeighbors = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)copyNeighborsname,
            sizeof(copyNeighborsname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get copyNeighbors symbol value.";
            // return self;
        }
        
        self.copyNeighbors = (void*)(plifecodebuffer + x);
        
        
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)MoveDwordsname,
            sizeof(MoveDwordsname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get MoveDwords symbol value.";
            // return self;
        }
        
        self.MoveDwords = (void*)(plifecodebuffer + x);
        
        
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)CalcNeighborsForRowNname,
            sizeof(CalcNeighborsForRowNname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get CalcNeighborsForRowN symbol value.";
            // return self;
        }
        
        self.CalcNeighborsForRowN = (void*)(plifecodebuffer + x);
        
        
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)UpdateCellsForRowNname,
            sizeof(UpdateCellsForRowNname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // myLabel.text = @"Could not get UpdateCellsForRowN symbol value.";
            // return self;
        }
        
        self.UpdateCellsForRowN = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)LifeBitMapOncename,
            sizeof(LifeBitMapOncename) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting LifeBitMapOnce symbol's value\n");
            // myLabel.text = @"Could not get LifeBitMapOnce symbol value.";
            // return self;
        }
    
        self.LifeBitMapOnce = (void*)(plifecodebuffer + x);
        */
        // printf("LifeBitMapOnceAddr = %llx\n", (uint64)(plifecodebuffer + x));

        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)AreaOrname,
            sizeof(AreaOrname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting AreaOr symbol's value\n");
            // myLabel.text = @"Could not get AreaOr symbol value.";
            // return self;
        }
    
        self.AreaOr = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)AreaNotSourceAndname,
            sizeof(AreaNotSourceAndname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting AreaNotSourceAnd symbol's value\n");
            // myLabel.text = @"Could not get AreaNotSourceAnd symbol value.";
            // return self;
        }
    
    
        self.AreaNotSourceAnd = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)AreaXorname,
            sizeof(AreaXorname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting AreaXor symbol's value\n");
            // myLabel.text = @"Could not get AreaXor symbol value.";
            // return self;
        }
    
        self.AreaXor = (void*)(plifecodebuffer + x);
        */
    /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)bitmapToPixelsname,
            sizeof(bitmapToPixelsname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting AreaXor symbol's value\n");
            // myLabel.text = @"Could not get AreaXor symbol value.";
            // return self;
        }
    
        self.bitmapToPixels = (void*)(plifecodebuffer + x);
 */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)getWrapOffsetname,
            sizeof(getWrapOffsetname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting getWrapOffset symbol's value\n");
            // myLabel.text = @"Could not get getWrapOffsetname symbol value.";
            // return self;
        }
    
        self.getWrapOffset = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)thisneighborsaddtblname,
            sizeof(thisneighborsaddtblname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting getWrapOffset symbol's value\n");
            // myLabel.text = @"Could not get getWrapOffsetname symbol value.";
            // return self;
        }
    
        self.pthisneighborsforeightcellstable = (void*)(plifecodebuffer + x);
        */
        /*
        x = self.dg_hsymbolnametovalue (
            self.pBHarrayhead,
            (uint64)nextneighborsaddtblname,
            sizeof(nextneighborsaddtblname) - 1,
            self.lifesymbollisthlistid,
            self.lifesymbollistelementid);
        
        if (self.dg_geterrorcount(self.pBHarrayhead) != 0)
        {
            // printf("got error getting getWrapOffset symbol's value\n");
            // myLabel.text = @"Could not get getWrapOffsetname symbol value.";
            // return self;
        }
    
        self.pnextneighborsforeightcellstable = (void*)(plifecodebuffer + x);
        */
    
        x = gamedevbitmapbufferlength;
    
        if (x > self.bitmapsize)
        {
            x = self.bitmapsize;
        }
    
        for (i = 0; i < self.bitmapsize; i++)
        {
            self.pbitmapbuffer[i] = 0;
        }
    
        for (i = 0; i < x; i++)
        {
            self.pbitmapbuffer[i] = ((unsigned char*)pgamedevbitmapbuffer)[i];
        }
    
        self.lifepending = false;
    
        self.cursorx = 0;
        self.cursory = 0;
        self.cursormode = 2; // 2 = xor
        self.cursorh = lifeformdoth;
        self.cursorw = lifeformdotw;
        self.pcursorlifeform = lifeformdot;

        self.CursorDrawFunction = self.AreaXor;
    
        // [self initNeighborsForEightCellsTable];
    
        // need to call CalcNeighborsForRow 256 times....
        // to build a table...
        //  clear first row of screen
        //  for i = 0 to 255
        //    store i to first byte of bitmap shifted 1 ... or go 0 and use plast word to get wrap...
        //    set dest pointers to row i of each lookup table
        //    set source pointer to pbitmap
        //    call CalcNeighborsForRow
        //  that's it
        /*
        self.mybitmapref = CGImageCreate(
            self.bitmapwidth,
            self.bitmapheight,
            1, // bits per component i.e. bits per color/alpha
            1, // bit per pixel
            self.bitmapwidth >> 8, // bytes per row
            );
        */
    
    self.myBaseColorSpace = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
    self.myColorSpace = CGColorSpaceCreateIndexed(
        self.myBaseColorSpace,
        1,
        myColorTable);
    
    self.myBitMapDataProvider = CGDataProviderCreateWithData(
        NULL, // data pointer passed to the release callback function
        self.pbitmapbuffer,
        self.bitmapsize,
        NULL); // CGDataProviderReleaseDataCallback
    
    self.myPixelBufferDataProvider = CGDataProviderCreateWithData(
        NULL, // data pointer passed to the release callback function
        self.ppixelbuffer1,
        self.pixelbuffersize,
        NULL); // CGDataProviderReleaseDataCallback
    
    /*
    self.myBitMapImageRef = CGImageCreate(
        self.bitmapwidth,
        self.bitmapheight,
        1, // bitsPerComponent,
        1, // bitsPerPixel,
        self.bitmapwidth / 8, // bytesPerRow,
        self.myColorSpace,
        0, // bitMapInfo,
        self.myBitMapDataProvider,
        NULL, // pdecode, NULL means don't allow remapping of color values
        false, // fshouldinterpolate,
        0); // color rendering intent.. 0 means default intent);
    
    self.myBitMapImageMaskRef = CGImageMaskCreate(
            self.bitmapwidth,
            self.bitmapheight,
            1, // bitsPerComponent,
            1, // size_t bitsPerPixel,
            self.bitmapwidth / 8, // bytesPerRow,
            self.myBitMapDataProvider,
            NULL, // const CGFloat *decode,
            false); // shouldInterpolate);
    */
    
    self.initwassuccessful = true;
}

- (void) AreaXorWithWrapUsingPdest:
                  (uint64) pdest
      Psrc:       (uint64) psrc
      DestWidthInBits:  (uint64) destWidthInBits
      DestHeightInBits: (uint64) destHeightInBits
      SrcWidthInBits:   (uint64) srcWidthInBits
      SrcHeightInBits:  (uint64) srcHeightInBits
      DestXInBits:      (uint64) destXInBits
      DestYInBits:      (uint64) destYInBits
{
    uint64 xWrapOffsetInBits;  // x offset in bits in src where wrap occurs
    uint64 yWrapOffsetInBits;  // y offset in bits in src where wrap occurs
    uint64 lastqwordinrowmask = 0;
    uint64 leftOverXbits; // bits in last U64 of src that still fit
    uint64 xWrapOffsetInBytes; // x offset in bytes in src where the left over bits start
    uint64 xWrapOffsetInU64s;
    uint64 srcWidthInU64s = (srcWidthInBits + 63) >> 6;
    uint64 xSrcLeftWidthInU64s = srcWidthInU64s;
    uint64 xSrcRightWidthInU64s = 0;
    
    uint64 srcWidthInU8s = srcWidthInU64s << 3;
    uint64 destWidthInU8s = destWidthInBits >> 3;
    // uint64 destWidthInUint64s = destWidthInBits >> 6;
    
    uint64 destXInU64s  = destXInBits >> 6;
    uint64 destXInBytes = destXInU64s << 3; // aligned to U64
    
    uint64 leftrowbump = 0;
    uint64 rightrowbump;
    
    lastqwordinrowmask = 0xFFFFFFFFFFFFFFFF;
    
    // srcwidthinqwords = self.dg_getnearesthighestmultiple (
    //    64,
    //    xwrapoffset);
    
    // could check overflow on these shifts...
    xWrapOffsetInBits = self.getWrapOffset(
        srcWidthInBits,
        destWidthInBits,
        destXInBits);
    
    yWrapOffsetInBits = self.getWrapOffset(
        srcHeightInBits,
        destHeightInBits,
        destYInBits);
    
    if (xWrapOffsetInBits == 0)
    {
        return;
    }
    
    if (yWrapOffsetInBits == 0)
    {
        return;
    }
    
    // src upper left
    leftOverXbits = xWrapOffsetInBits & 0x3F;
    xWrapOffsetInU64s = xWrapOffsetInBits >> 6;
    xWrapOffsetInBytes = xWrapOffsetInU64s << 3;
    
    lastqwordinrowmask = bitmasktable[leftOverXbits];
    
    if (xWrapOffsetInBits < srcWidthInBits)
    {
        if (0 == leftOverXbits)
        {
            xSrcLeftWidthInU64s = xWrapOffsetInU64s;
            xSrcRightWidthInU64s = srcWidthInU64s - xWrapOffsetInU64s;
        }
        else
        {
            xSrcLeftWidthInU64s = xWrapOffsetInU64s + 1;
            xSrcRightWidthInU64s = srcWidthInU64s - xWrapOffsetInU64s;
        }
    }
    
    leftrowbump = (srcWidthInU64s - xSrcLeftWidthInU64s) << 3;
    rightrowbump = (srcWidthInU64s - xSrcRightWidthInU64s) << 3;
    
    self.CursorDrawFunction(
        pdest + (destYInBits * destWidthInU8s) +  destXInBytes,
        psrc,
        yWrapOffsetInBits, // srcheightinbits,
        xSrcLeftWidthInU64s,
        (destXInBits & 0x3F), // srcxinbitsdestxinbits,
        destWidthInBits,
        lastqwordinrowmask,
        leftrowbump);
    
    // src lower left wrap to top of dest
    if (yWrapOffsetInBits < srcHeightInBits)
    {
        self.CursorDrawFunction(
            pdest + destXInBytes,
            psrc + (yWrapOffsetInBits * srcWidthInU8s),
            srcHeightInBits - yWrapOffsetInBits, // srcheightinbits,
            xSrcLeftWidthInU64s,
            (destXInBits & 0x3F), // srcxinbitsdestxinbits,
            destWidthInBits,
            lastqwordinrowmask,
            leftrowbump);
        
        if (xWrapOffsetInBits < srcWidthInBits)
        {
            // src lower right
            self.CursorDrawFunction(
                pdest,
                psrc + (yWrapOffsetInBits * srcWidthInU8s) + xWrapOffsetInBytes,
                srcHeightInBits - yWrapOffsetInBits, // srcheightinbits,
                xSrcRightWidthInU64s,
                (leftOverXbits << 8), // srcxinbitsdestxinbits,
                destWidthInBits,
                0xFFFFFFFFFFFFFFFF,
                rightrowbump);
        }
    }
    
    // src upper right to left of dest
    if (xWrapOffsetInBits < srcWidthInBits)
    {
        self.CursorDrawFunction(
            pdest + (destYInBits * destWidthInU8s),
            psrc + xWrapOffsetInBytes,
            yWrapOffsetInBits, // srcheightinbits,
            xSrcRightWidthInU64s,
            (leftOverXbits << 8), // srcxinbitsdestxinbits,
            destWidthInBits,
            0xFFFFFFFFFFFFFFFF,
            rightrowbump);
    }
    
}

@end

    /*
    else
            {
                NSAlert *alert = [[NSAlert alloc] init];
                NSString *myalertstring = [NSString init];
                myalertstring = [myalertstring initWithCString: myfilenamebuf encoding: NSASCIIStringEncoding];
                [alert addButtonWithTitle:@"Could not open file!"];
                [alert setInformativeText: myalertstring];
                [alert setAlertStyle:NSWarningAlertStyle];
                    
                [alert runModal];
                // [alert release];
            }
        }
    */

    /*
        */
