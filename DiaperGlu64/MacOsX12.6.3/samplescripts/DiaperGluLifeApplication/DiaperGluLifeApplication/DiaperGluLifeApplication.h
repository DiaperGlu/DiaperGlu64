//
//  DiaperGluLifeApplication.h
//  DiaperGluLifeApplication
//
//  Created by James Norris on 4/8/18.
//  Copyright (c) 2018 James Norris. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DiaperGluLifeOpenGLView.h"
#import "DiaperGluLifeAppDelegate.h"
#include <dlfcn.h>
#include <sys/stat.h>
#include <OpenGL/gl.h>
// #include "liblife.h"

const static uint64 lifeformdotw = 1;
const static uint64 lifeformdoth = 1;
uint64 static lifeformdot[1] = { 0x0000000000000080 }; // little endian

const static uint64 lifeformblinkerw = 3;
const static uint64 lifeformblinkerh = 1;
uint64 static lifeformblinker[1] = { 0x00000000000000E0 }; // little endian

const static uint64 lifeformtoadw = 3;
const static uint64 lifeformtoadh = 2;
uint64 static lifeformtoad[2] = {
    0x00000000000000E0, 
    0x0000000000000070 };

const static uint64 lifeformbeaconw = 6;
const static uint64 lifeformbeaconh = 4;
uint64 static lifeformbeacon[4] = {
    0x00000000000000C0, 
    0x00000000000000C0,
    0x000000000000000C,
    0x000000000000000C };

const static uint64 lifeformgliderw = 3;
const static uint64 lifeformgliderh = 3;
uint64 static lifeformglider[3] = {
    0x00000000000000E0, // little endian
    0x0000000000000080 , // little endian
    0x0000000000000040 }; // little endian

const static uint64 lifeformsmallspaceshipw = 5;
const static uint64 lifeformsmallspaceshiph = 4;
uint64 static lifeformsmallspaceship[4] = {
    0x00000000000000F0, 
    0x0000000000000088 , 
    0x0000000000000080,
    0x0000000000000040 };


const static uint64 lifeformcopperheadw = 8;
const static uint64 lifeformcopperheadh = 12;
uint64 static lifeformcopperhead[12] = {
    0x0000000000000066,
    0x0000000000000018,
    0x0000000000000018,
    0x00000000000000A5,
    0x0000000000000081,
    0x0000000000000000,
    0x0000000000000081,
    0x0000000000000066,
    0x000000000000003C,
    0x0000000000000000,
    0x0000000000000018,
    0x0000000000000018 };

const static uint64 lifeformblock4w = 2;
const static uint64 lifeformblock4h = 2;
uint64 static lifeformblock4[2] = {
    0x00000000000000C0, // little endian
    0x00000000000000C0 }; // little endian

const static uint64 lifeformbeehivew = 4;
const static uint64 lifeformbeehiveh = 3;
uint64 static lifeformbeehive[3] = {
    0x0000000000000060, 
    0x0000000000000090,
    0x0000000000000060 };

const static uint64 lifeformbreadw = 4;
const static uint64 lifeformbreadh = 4;
uint64 static lifeformbread[4] = {
    0x0000000000000060, 
    0x0000000000000090,
    0x00000000000000A0,
    0x0000000000000040 };

const static uint64 lifeformboatw = 3;
const static uint64 lifeformboath = 3;
uint64 static lifeformboat[3] = {
    0x00000000000000C0, 
    0x00000000000000A0,
    0x0000000000000040 };

const static uint64 lifeformtubw = 3;
const static uint64 lifeformtubh = 3;
uint64 static lifeformtub[3] = {
    0x0000000000000040, 
    0x00000000000000A0,
    0x0000000000000040 };

const static uint64 lifeformladderw = 5;
const static uint64 lifeformladderh = 5;
uint64 static lifeformladder[5] = {
    0x00000000000000E8,
    0x0000000000000080,
    0x0000000000000018,
    0x0000000000000068,
    0x00000000000000A8 };

const static uint64 lifeformacornw = 7;
const static uint64 lifeformacornh = 3;
uint64 static lifeformacorn[3] = {
    0x0000000000000040, 
    0x0000000000000010,
    0x00000000000000CE };

const static uint64 lifeformrpentaminow = 3;
const static uint64 lifeformrpentaminoh = 3;
uint64 static lifeformrpentamino[3] = {
    0x0000000000000060,
    0x00000000000000C0,
    0x0000000000000040 };

const static uint64 lifeformrabbitsw = 7;
const static uint64 lifeformrabbitsh = 3;
uint64 static lifeformrabbits[3] = {
    0x000000000000008E,
    0x00000000000000E4,
    0x0000000000000040 };

/*
const static uint64 lifeformtestw = 2;
const static uint64 lifeformtesth = 3;
uint64 static lifeformtest[6] = {
    0x1122334455667788, 0x99aabbccddeeffef,
    0x1122334455667788, 0x99aabbccddeeffef,
    0x1122334455667788, 0x99aabbccddeeffef
};
*/

const static uint64 bitmasktable[64] = {
    0xFFFFFFFFFFFFFFFF,
    0x8000000000000000,
    0xC000000000000000,
    0xE000000000000000,
    0xF000000000000000,

    0xF800000000000000,
    0xFC00000000000000,
    0xFE00000000000000,
    0xFF00000000000000,

    0xFF80000000000000,
    0xFFC0000000000000,
    0xFFE0000000000000,
    0xFFF0000000000000,

    0xFFF8000000000000,
    0xFFFC000000000000,
    0xFFFE000000000000,
    0xFFFF000000000000,


    0xFFFF800000000000,
    0xFFFFC00000000000,
    0xFFFFE00000000000,
    0xFFFFF00000000000,

    0xFFFFF80000000000,
    0xFFFFFC0000000000,
    0xFFFFFE0000000000,
    0xFFFFFF0000000000,

    0xFFFFFF8000000000,
    0xFFFFFFC000000000,
    0xFFFFFFE000000000,
    0xFFFFFFF000000000,

    0xFFFFFFF800000000,
    0xFFFFFFFC00000000,
    0xFFFFFFFE00000000,
    0xFFFFFFFF00000000,


    0xFFFFFFFF80000000,
    0xFFFFFFFFC0000000,
    0xFFFFFFFFE0000000,
    0xFFFFFFFFF0000000,

    0xFFFFFFFFF8000000,
    0xFFFFFFFFFC000000,
    0xFFFFFFFFFE000000,
    0xFFFFFFFFFF000000,

    0xFFFFFFFFFF800000,
    0xFFFFFFFFFFC00000,
    0xFFFFFFFFFFE00000,
    0xFFFFFFFFFFF00000,

    0xFFFFFFFFFFF80000,
    0xFFFFFFFFFFFC0000,
    0xFFFFFFFFFFFE0000,
    0xFFFFFFFFFFFF0000,


    0xFFFFFFFFFFFF8000,
    0xFFFFFFFFFFFFC000,
    0xFFFFFFFFFFFFE000,
    0xFFFFFFFFFFFFF000,

    0xFFFFFFFFFFFFF800,
    0xFFFFFFFFFFFFFC00,
    0xFFFFFFFFFFFFFE00,
    0xFFFFFFFFFFFFFF00,

    0xFFFFFFFFFFFFFF80,
    0xFFFFFFFFFFFFFFC0,
    0xFFFFFFFFFFFFFFE0,
    0xFFFFFFFFFFFFFFF0,

    0xFFFFFFFFFFFFFFF8,
    0xFFFFFFFFFFFFFFFC,
    0xFFFFFFFFFFFFFFFE};

const static unsigned char myColorTable[6] = { 0, 0, 0, 255, 255, 255};

@interface DiaperGluLifeApplication : NSApplication

- (void) loadBitmap;
- (void) saveBitmap;

- (void) initLife;

- (void) cursorDown;
- (void) cursorUp;
- (void) cursorRight;
- (void) cursorLeft;

- (void) clearatcursor;
- (void) setatcursor;
- (void) toggleatcursor;
- (void) drawlifeformatcursor;

- (void) clearBitmap;

- (void) AreaXorWithWrapUsingPdest:
                  (uint64) pdest
      Psrc:       (uint64) psrc
      DestWidthInBits:  (uint64) destWidthInBits
      DestHeightInBits: (uint64) destHeightInBits
      SrcWidthInBits:   (uint64) srcWidthInBits
      SrcHeightInBits:  (uint64) srcHeightInBits
      DestXInBits:      (uint64) destXInBits
      DestYInBits:      (uint64) destYInBits;

@property DiaperGluLifeOpenGLView* myView;
@property DiaperGluLifeAppDelegate* myAppDelegate;

@property bool initwassuccessful;

// @property bool notfirsttimethrough;
@property bool fullspeed;
@property bool lifepending;
@property bool islifing;
@property bool islifingonce;

@property uint64 frameskip;

@property uint64 bitmapwidth;
@property uint64 bitmapheight;
@property uint64 bitmapsize;
@property uint64 pixelbuffersize;

@property uint64 cursorx;
@property uint64 cursory;
@property uint64 cursormode; // 0 = clear, 1 = set, 2 = xor
@property uint64 cursorw; // in uint64s
@property uint64 cursorh; // in bits
@property uint64* pcursorlifeform;

@property uint64 logicfunction;
  // 0xe0 = normal life rules
  // bit 0 = f(dead cell with 0 neighbors)
  // bit 1 = f(live cell with 0 neighbors)
  // bit 2 = f(dead cell with 1 neighbors)
  // bit 3 = f(live cell with 1 neighbors)
  // bit 4 = f(dead cell with 2 neighbors)
  // bit 5 = 5(live cell with 2 neighbors)
  // etc..

@property CGColorSpaceRef myBaseColorSpace;
@property CGColorSpaceRef myColorSpace;
@property CGDataProviderRef myBitMapDataProvider;
@property CGDataProviderRef myPixelBufferDataProvider;
@property CGImageRef myBitMapImageRef;
@property CGImageRef myBitMapImageMaskRef;

@property unsigned char* pbitmapbuffer;
@property unsigned char* ptoprowneighbors;
@property unsigned char* ppreviousrowneighbors;
@property unsigned char* pthisrowneighbors;
@property unsigned char* pnextrownneighbors;

@property unsigned char* pthisneighborsforeightcellstable;
@property unsigned char* pnextneighborsforeightcellstable;

@property unsigned char* ppixelbuffer1;

@property void* hdiaperglulib;
@property void* hlifelib;
// @property void* hdg2dgraphicslib;
@property uint64 pBHarrayhead;

@property CGImageRef mybitmapref;

@property uint64 (*dg_init)(int argc, char* argv[]);
@property uint64 (*dg_loadfile)(
    uint64 pBHarrayhead,
    uint64 pfilename,
    uint64 filenamelength);
@property uint64 (*dg_nglufile)(
    uint64 pBHarrayhead,
    uint64 pfilename,
    uint64 filenamelength);
@property uint64 (*dg_getnamedsymbollisthideid) (
    uint64 pBHarrayhead,
    uint64 psymbollistname,
    uint64 symbollistnamelength,
    uint64 phlistid);
@property uint64 (*dg_hsymbolnametovalue) (
    uint64 pBHarrayhead,
    uint64 psymbolname,
    uint64 symbolnamelength,
    uint64 namedsymbollisthlistid,
    uint64 namedsymbollistelementid);
@property uint64 (*dg_getpbuffer) (
    uint64 pBHarrayhead,
    uint64 bufferid,
    uint64 pplength);
@property uint64 (*dg_getpbufferoffset)  (
    uint64 pBHarrayhead,
    uint64 bufferid,
    uint64 offset);
@property uint64 (*dg_geterrorcount) (uint64 pBHarrayhead);
@property uint64 (*dg_poperror) (uint64 pBHarrayhead);
// @property uint64 (*dg_bswap) (uint64 x);

@property uint64 gamedevbitmapbufferid;
@property uint64 lifelibbufferid;
@property uint64 lifesymbollisthlistid;
@property uint64 lifesymbollistelementid;

@property uint64 (*dg_getoverlapsegment) (
    uint64 ASX,
    uint64 AL,
    uint64 BSX,
    uint64 BL,
    uint64 pOVERLAPSX);

@property uint64 (*CalcNeighborsForRow) (
    uint64 prowbits,
    uint64 pthisrownneighbors,
    uint64 pnextrownneighbors,
    uint64 dwordsperrow,
    uint64 pthisrownneighborsend,
    uint64 pnextrownneighborsend);

@property uint64 (*UpdateCellsForRow) (
    uint64 prowbits,
    uint64 ppreviousrownneighbors,
    uint64 pnextrownneighbors,
    uint64 dwordsperrow,
    uint64 logicfunction);
/*
@property uint64 (*ClearNeighbors) (
    uint64 ppreviousrownneighbors,
    uint64 pthisneighborsbuffer,
    uint64 pnextrownneighbors,
    uint64 rowsizeindwords);
*/
@property uint64 (*copyNeighbors) (
    uint64 ppreviousrownneighbors,
    uint64 pthisneighborsbuffer,
    uint64 pnextrownneighbors,
    uint64 rowsizeindwords);

@property uint64 (*MoveDwords) (
    uint64 psrc,
    uint64 pdest,
    uint64 lengthindwords);

@property uint64 (*CalcNeighborsForRowN) (
    uint64 rowN,
    uint64 pthisrownneighbors,
    uint64 pnextrownneighbors,
    uint64 myscreenwidth,
    uint64 pmypixelbuffer);

@property uint64 (*UpdateCellsForRowN) (
    uint64 rowN,
    uint64 ppreviousrowneighbors,
    uint64 pnextrownneighbors,
    uint64 myscreenwidth,
    uint64 pmypixelbuffer,
    uint64 logicfunction);

@property uint64 (*LifeBitMapOnce) (
    uint64 ppreviousrowneighbors,
    uint64 pthisrowneighbors,
    uint64 pnextrownneighbors,
    uint64 myscreenwidth,
    uint64 myscreenheight,
    uint64 pmypixelbuffer,
    uint64 logicfunction,
    uint64 ptoprowneighbors);

@property uint64 (*AreaXor) (
    uint64 pdest,
    uint64 psrc,
    uint64 srcheightinbits,
    uint64 srcwidthtodoinbits,
    uint64 srcxinbitsdestxinbits,
    uint64 destwidthinbits,
    uint64 lastqwordinrowmask,
    uint64 srcendofrowbumpinbytes);

@property uint64 (*AreaOr) (
    uint64 pdest,
    uint64 psrc,
    uint64 srcheightinbits,
    uint64 srcwidthtodoinu64s,
    uint64 srcxinbitsdestxinbits,
    uint64 destwidthinqwords,
    uint64 lastqwordinrowmask,
    uint64 srcendofrowbumpinbytes);

@property uint64 (*AreaNotSourceAnd) (
    uint64 pdest,
    uint64 psrc,
    uint64 srcheightinbits,
    uint64 srcwidthtodoinu64s,
    uint64 srcxinbitsdestxinbits,
    uint64 destwidthinqwords,
    uint64 lastqwordinrowmask,
    uint64 srcendofrowbumpinbytes);

@property uint64 (*CursorDrawFunction) (
    uint64 pdest,
    uint64 psrc,
    uint64 srcheightinbits,
    uint64 srcwidthtodoinu64s,
    uint64 srcxinbitsdestxinbits,
    uint64 destwidthinqwords,
    uint64 lastqwordinrowmask,
    uint64 srcendofrowbumpinbytes);

@property uint64 (*getWrapOffset) (
    uint64 srcwidth,
    uint64 destwidth,
    uint64 destx);

/*
@property uint64 (*bitmapToPixels) (
    uint64 destpixels,            // rdi
    uint64 srcbitmap,             // rsi
    uint64 clearpixelvalue,       // rdx
    uint64 bitmapsizeinuint8s,    // rcx
    uint64 setpixelvalue);        // r8
*/
@end
