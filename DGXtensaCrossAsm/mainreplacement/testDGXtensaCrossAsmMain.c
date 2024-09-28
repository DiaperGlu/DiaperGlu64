/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "testDGXtensaCrossAsm.h"

void app_main(void)
{
    int testexportresult = 0x41234587;
    float testexportsfresult = 0.0;

    printf("Hello world!\n");


    testexportresult = testXTMOVI();

    printf("\nTesting XTMOVI, : Expected 0x37, got %x", testexportresult);


    testexportresult = testXTMOVN();

    printf("\nTesting XTMOV.N, : Expected 0x38, got %x", testexportresult);


    testexportresult = testXTJ();

    printf("\nTesting XTJ, : Expected 0x51, got %x", testexportresult);


    testexportresult = testXTS32INL32IN();

    printf("\nTesting XTS32INL32IN, : Expected 0x27, got %x", testexportresult);


    testexportresult = testXTBEQ();

    printf("\nTesting XTBEQ, eq case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBEQb();

    printf("\nTesting XTBEQ, ne b case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBEQc();

    printf("\nTesting XTBEQ, ne c case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBGE();

    printf("\nTesting XTBGE, = case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBGEb();

    printf("\nTesting XTBGE, > b case: Expected 0x32, got %x", testexportresult);


    testexportresult = testXTBEQc();

    printf("\nTesting XTBEQ, ne c case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLT();

    printf("\nTesting XTBLT, = case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTb();

    printf("\nTesting XTBLT, > b case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTc();

    printf("\nTesting XTBLT, < c case: Expected 0x30, got %x", testexportresult);


    testexportresult = testXTBNE();

    printf("\nTesting XTBNE, = case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNEb();

    printf("\nTesting XTBNE, > b case: Expected 0x32, got %x", testexportresult);


    testexportresult = testXTBNEc();

    printf("\nTesting XTBNE, < c case: Expected 0x30, got %x", testexportresult);


    testexportresult = testXTBLTU();

    printf("\nTesting XTBLTU, = case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTUb();

    printf("\nTesting XTBLTU, > b case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTUc();

    printf("\nTesting XTBLTU, < c case: Expected 0x30, got %x", testexportresult);


    testexportresult = testXTBEQZ();

    printf("\nTesting XTBEQZ, = case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBEQZb();

    printf("\nTesting XTBEQZ, > b case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBEQZc();

    printf("\nTesting XTBEQZ, < c case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBGEZ();

    printf("\nTesting XTBGEZ, = case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBGEZb();

    printf("\nTesting XTBGEZ, > b case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBGEZc();

    printf("\nTesting XTBGEZ, < c case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTZ();

    printf("\nTesting XTBLTZ, = case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTZb();

    printf("\nTesting XTBLTZ, > b case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBLTZc();

    printf("\nTesting XTBLTZ, < c case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBNEZ();

    printf("\nTesting XTBNEZ, = case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNEZb();

    printf("\nTesting XTBNEZ, > b case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBNEZc();

    printf("\nTesting XTBNEZ, < c case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTL32R();

    printf("\nTesting XTL32R, Expected 0x11213141, got %x", testexportresult);


    testexportresult = testXTCALL0();

    printf("\nTesting XTCALL0, Expected 0x52, got %x", testexportresult);


    testexportresult = testXTADDN();

    printf("\nTesting XTADD.N, Expected 0x34, got %x", testexportresult);


    testexportresult = testXTADDNb();

    printf("\nTesting XTADD.Nb, Expected 0x34, got %x", testexportresult);


    testexportresult = testXTADD();

    printf("\nTesting XTADD, Expected 0x34, got %x", testexportresult);


    testexportresult = testXTADDb();

    printf("\nTesting XTADDb, Expected 0x34, got %x", testexportresult);


    testexportresult = testXTADDI();

    printf("\nTesting XTADDI, Expected 0x66, got %x", testexportresult);


    testexportresult = testXTADDIN();

    printf("\nTesting XTADDI.N, Expected 0x22, got %x", testexportresult);


    testexportresult = testXTADDMI();

    printf("\nTesting XTADDMI, Expected 0x4723, got %x", testexportresult);


    testexportresult = testXTADDX2();

    printf("\nTesting XTADDX2, Expected 0x57, got %x", testexportresult);


    testexportresult = testXTADDX4();

    printf("\nTesting XTADDX4, Expected 0x9D, got %x", testexportresult);


    testexportresult = testXTADDX8();

    printf("\nTesting XTADDX8, Expected 0x129, got %x", testexportresult);


    testexportresult = testXTAND();

    printf("\nTesting XTAND, Expected 0x01, got %x", testexportresult);


    testexportresult = testXTOR();

    printf("\nTesting XTOR, Expected 0x33, got %x", testexportresult);


    testexportresult = testXTXOR();

    printf("\nTesting XTXOR, Expected 0x32, got %x", testexportresult);


    testexportresult = testXTSUB();

    printf("\nTesting XTSUB, Expected 0x12, got %x", testexportresult);


    testexportresult = testXTSUBX2();

    printf("\nTesting XTSUBX2, Expected 0x35, got %x", testexportresult);


    testexportresult = testXTSUBX4();

    printf("\nTesting XTSUBX4, Expected 0x7B, got %x", testexportresult);


    testexportresult = testXTSUBX8();

    printf("\nTesting XTSUBX8, Expected 0x107, got %x", testexportresult);


    testexportresult = testXTMIN();

    printf("\nTesting XTMIN, Expected -0x23, got %x", testexportresult);


    testexportresult = testXTMINU();

    printf("\nTesting XTMINU, Expected 0x11, got %x", testexportresult);


    testexportresult = testXTMAX();

    printf("\nTesting XTMAX, Expected 0x11, got %x", testexportresult);


    testexportresult = testXTMAXU();

    printf("\nTesting XTMAXU, Expected -0x23, got %x", testexportresult);


    testexportresult = getBaseAddress();

    printf("\nBase Address is %x", testexportresult);


    testexportresult = testXTMOV();

    printf("\nTesting XTMOV, Expected 0x39, got %x", testexportresult);


    testXTNOP();

    printf("\nTesting XTNOP, crash test");


    testexportresult = testXTABS();

    printf("\nTesting XTABS, Expected 0x51, got %x", testexportresult);


    testexportsfresult = testXTUFLOATS();

    printf("\nTesting XTUFLOATS, Expected 2.0, got %g", testexportsfresult);


    testexportresult = testXTMUL16S();

    printf("\nTesting XTMUL16S, Expected -0x6, got %x", testexportresult);


    testexportresult = testXTMUL16U();

    printf("\nTesting XTMUL16U, Expected 0x6, got %x", testexportresult);


    testexportresult = testXTSALT();

    printf("\nTesting XTSALT, Expected 0x1, got %x", testexportresult);


    testexportresult = testXTSALTU();

    printf("\nTesting XTSALTU, Expected 0x0, got %x", testexportresult);


    testexportresult = testXTSEXT();

    printf("\nTesting XTSEXT, Expected 0xFFFFFF80, got %x", testexportresult);


    testexportresult = testXTSLLI();

    printf("\nTesting XTSLLI, Expected 0x800, got %x", testexportresult);


    testexportresult = testXTNEG();

    printf("\nTesting XTNEG, Expected 0x7E, got %x", testexportresult);


    // testexportresult = testXTDEPBITS();

    // printf("\nTesting XTDEPBITS, Expected 0xFFF18FFF, got %x", testexportresult);


    testexportsfresult = testXTADDS();

    printf("\nTesting XTADD.S, Expected 5.0, got %g", testexportsfresult);


    testexportresult = testXTCEILS();

    printf("\nTesting XTCEIL.S, Expected 0x2, got %x", testexportresult);


    testexportresult = testXTMOVEQZ();

    printf("\nTesting XTMOVEQZ, Expected 0x29, got %x", testexportresult);


    testexportresult = testXTMOVEQZb();

    printf("\nTesting XTMOVEQZ, b Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVEQZc();

    printf("\nTesting XTMOVEQZ, c Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVGEZ();

    printf("\nTesting XTMOVGEZ, Expected 0x29, got %x", testexportresult);


    testexportresult = testXTMOVGEZb();

    printf("\nTesting XTMOVGEZ, b Expected 0x29, got %x", testexportresult);


    testexportresult = testXTMOVGEZc();

    printf("\nTesting XTMOVGEZ, c Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVLTZ();

    printf("\nTesting XTMOVLTZ, Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVLTZb();

    printf("\nTesting XTMOVLTZ, b Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVLTZc();

    printf("\nTesting XTMOVLTZ, c Expected 0x29, got %x", testexportresult);


    testexportresult = testXTMOVGEZc();

    printf("\nTesting XTMOVGEZ, c Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVNEZ();

    printf("\nTesting XTMOVNEZ, Expected -0x1, got %x", testexportresult);


    testexportresult = testXTMOVNEZb();

    printf("\nTesting XTMOVNEZ, b Expected 0x29, got %x", testexportresult);


    testexportresult = testXTMOVNEZc();

    printf("\nTesting XTMOVNEZ, c Expected 0x29, got %x", testexportresult);


    testexportresult = testXTRFR();

    printf("\nTesting XTRFR, Expected 0x40000000, got %x\n note: the WindowError thingy is not an error, the monitor just does not like 0x40000000", testexportresult);


    testexportresult = testXTWFR();

    printf("\nTesting XTWFR, Expected 0x0, got %x", testexportresult);


    testexportsfresult = testXTMADDS();

    printf("\nTesting XTMADD.S, Expected 7.0, got %g", testexportsfresult);


    testexportsfresult = testXTMADDNS();

    printf("\nTesting XTMADDN.S, Expected 7.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVS();

    printf("\nTesting XTMOV.S, Expected 2.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVEQZS();

    printf("\nTesting XTMOVEQZS, Expected 41.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVEQZSb();

    printf("\nTesting XTMOVEQZS, b Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVEQZSc();

    printf("\nTesting XTMOVEQZS, c Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVGEZS();

    printf("\nTesting XTMOVGEZS, Expected 41.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVGEZSb();

    printf("\nTesting XTMOVGEZS, b Expected 41.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVGEZSc();

    printf("\nTesting XTMOVGEZS, c Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVLTZS();

    printf("\nTesting XTMOVLTZS, Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVLTZSb();

    printf("\nTesting XTMOVLTZS, b Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVLTZSc();

    printf("\nTesting XTMOVLTZS, c Expected 41.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVGEZSc();

    printf("\nTesting XTMOVGEZS, c Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVNEZS();

    printf("\nTesting XTMOVNEZS, Expected 7, got %g", testexportsfresult);


    testexportsfresult = testXTMOVNEZSb();

    printf("\nTesting XTMOVNEZS, b Expected 41.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVNEZSc();

    printf("\nTesting XTMOVNEZS, c Expected 41.0, got %g", testexportsfresult);


    testexportsfresult = testXTMSUBS();

    printf("\nTesting XTMSUB.S, Expected -5.0, got %g", testexportsfresult);


    testexportresult = testXTMULL();

    printf("\nTesting XTMULL, Expected 6, got %x", testexportresult);


    testexportresult = testXTMULSH();

    printf("\nTesting XTMULSH, Expected -1, got %x", testexportresult);


    testexportresult = testXTMULUH();

    printf("\nTesting XTMULUH, Expected 1, got %x", testexportresult);


    testexportresult = testXTSLL();

    printf("\nTesting XTSLL, Expected 0x0C, got %x", testexportresult);


    testexportresult = testXTRSR();

    printf("\nTesting XTRSR, Expected 0x1E, got %x", testexportresult);


    testexportresult = testXTOEQS();

    printf("\nTesting XTOEQ.S, Expected 0x4, got %x", testexportresult);


    testexportresult = testXTOEQSb();

    printf("\nTesting XTOEQ.S, b Expected 0x0, got %x", testexportresult);


    testexportresult = testXTOEQSc();

    printf("\nTesting XTOEQ.S, c Expected 0x0, got %x", testexportresult);


    testexportresult = testXTOLES();

    printf("\nTesting XTOLE.S, Expected 0x4, got %x", testexportresult);


    testexportresult = testXTOLESb();

    printf("\nTesting XTOLE.S, b Expected 0x4, got %x", testexportresult);


    testexportresult = testXTOLESc();

    printf("\nTesting XTOLE.S, c Expected 0x0, got %x", testexportresult);


    testexportresult = testXTOLTS();

    printf("\nTesting XTOLT.S, Expected 0x0, got %x", testexportresult);


    testexportresult = testXTOLTSb();

    printf("\nTesting XTOLT.S, b Expected 0x4, got %x", testexportresult);


    testexportresult = testXTOLTSc();

    printf("\nTesting XTOLT.S, c Expected 0x0, got %x", testexportresult);


    testexportresult = testXTANDB0();

    printf("\nTesting XTANDB, 0 and 0 Expected 0x0, got %x", testexportresult);


    testexportresult = testXTANDB1();

    printf("\nTesting XTANDB, 1 and 0 Expected 0x1, got %x", testexportresult);


    testexportresult = testXTANDB2();

    printf("\nTesting XTANDB, 0 and 1 Expected 0x2, got %x", testexportresult);


    testexportresult = testXTANDB3();

    printf("\nTesting XTANDB, 1 and 1 Expected 0x7, got %x", testexportresult);


    testexportresult = testXTANDBC0();

    printf("\nTesting XTANDBC, not0 and 0 Expected 0x0, got %x", testexportresult);


    testexportresult = testXTANDBC1();

    printf("\nTesting XTANDBC, not1 and 0 Expected 0x1, got %x", testexportresult);


    testexportresult = testXTANDBC2();

    printf("\nTesting XTANDBC, not0 and 1 Expected 0x6, got %x", testexportresult);


    testexportresult = testXTANDBC3();

    printf("\nTesting XTANDBC, not1 and 1 Expected 0x3, got %x", testexportresult);


    testexportresult = testXTORB0();

    printf("\nTesting XTORB, 0 and 0 Expected 0x0, got %x", testexportresult);


    testexportresult = testXTORB1();

    printf("\nTesting XTORB, 1 and 0 Expected 0x5, got %x", testexportresult);


    testexportresult = testXTORB2();

    printf("\nTesting XTORB, 0 and 1 Expected 0x6, got %x", testexportresult);


    testexportresult = testXTORB3();

    printf("\nTesting XTORB, 1 and 1 Expected 0x7, got %x", testexportresult);


    testexportresult = testXTORBC0();

    printf("\nTesting XTORBC, not0 and 4 Expected 0x4, got %x", testexportresult);


    testexportresult = testXTORBC1();

    printf("\nTesting XTORBC, not1 and 0 Expected 0x1, got %x", testexportresult);


    testexportresult = testXTORBC2();

    printf("\nTesting XTORBC, not0 and 1 Expected 0x6, got %x", testexportresult);


    testexportresult = testXTORBC3();

    printf("\nTesting XTORBC, not1 and 1 Expected 0x7, got %x", testexportresult);


    testexportresult = testXTXORB0();

    printf("\nTesting XTXORB, 0 xor 0 Expected 0x0, got %x", testexportresult);


    testexportresult = testXTXORB1();

    printf("\nTesting XTXORB, 1 xor 0 Expected 0x5, got %x", testexportresult);


    testexportresult = testXTXORB2();

    printf("\nTesting XTXORB, 0 xor 1 Expected 0x6, got %x", testexportresult);


    testexportresult = testXTXORB3();

    printf("\nTesting XTXORB, 1 xor 1 Expected 0x3, got %x", testexportresult);


    testexportresult = testXTQUOS();

    printf("\nTesting XTQUOS, Expected -0x2, got %x", testexportresult);


    testexportresult = testXTQUOU();

    printf("\nTesting XTQUOU, Expected 0x2, got %x", testexportresult);


    testexportresult = testXTREMS();

    printf("\nTesting XTREMS, Expected -0x1, got %x", testexportresult);


    testexportresult = testXTREMU();

    printf("\nTesting XTREMU, Expected 0x1, got %x", testexportresult);


    testexportresult = testXTMOVF();

    printf("\nTesting XTMOVF, Expected 0x7, got %x", testexportresult);


    testexportresult = testXTMOVFb();

    printf("\nTesting XTMOVFb, Expected 0x1, got %x", testexportresult);


    testexportresult = testXTMOVT();

    printf("\nTesting XTMOVT, Expected 0x0, got %x", testexportresult);


    testexportresult = testXTMOVTb();

    printf("\nTesting XTMOVTb, Expected 0x7, got %x", testexportresult);


    testexportsfresult = testXTMOVFS();

    printf("\nTesting XTMOVF.S, Expected 7.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVFSb();

    printf("\nTesting XTMOVF.S, b Expected 1.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVTS();

    printf("\nTesting XTMOVT.S, Expected 1.0, got %g", testexportsfresult);


    testexportsfresult = testXTMOVTSb();

    printf("\nTesting XTMOVT.S, b Expected 7.0, got %g", testexportsfresult);


    testexportsfresult = testXTFLOATS();

    printf("\nTesting XTFLOAT.S, Expected -9.0, got %g", testexportsfresult);


    testexportresult = testXTROUNDS();

    printf("\nTesting XTROUND.S, Expected -0x9, got %x", testexportresult);


    testexportresult = testXTFLOORS();

    printf("\nTesting XTFLOOR.S, Expected -0x9, got %x", testexportresult);


    testexportsfresult = testXTSUBS();

    printf("\nTesting XTSUB.S, Expected 4.0, got %g", testexportsfresult);


    testexportresult = testXTTRUNCS();

    printf("\nTesting XTTRUNC.S, Expected -0x9, got %x", testexportresult);


    testexportresult = testXTSRC();

    printf("\nTesting XTSRC, Expected 0x8000000F, got %x", testexportresult);


    testexportresult = testXTSRLI();

    printf("\nTesting XTSRLI, Expected 0x1F, got %x", testexportresult);


    testexportresult = testXTCLAMPSa();

    printf("\nTesting XTCLAMPS, a Expected 0x7F, got %x", testexportresult);


    testexportresult = testXTCLAMPSb();

    printf("\nTesting XTCLAMPS, b Expected 0x7f, got %x", testexportresult);


    testexportsfresult = testXTLSX();

    printf("\nTesting XTLSX, Expected 98.0, got %g", testexportsfresult);


    testexportsfresult = testXTLSXPa();

    printf("\nTesting XTLSXP, a Expected 98.0, got %g", testexportsfresult);


    testexportresult = testXTLSXPb();

    printf("\nTesting XTLSXP, b Expected 0x4, got %x", testexportresult);


    testexportsfresult = testXTLSXUa();

    printf("\nTesting XTLSXU, a Expected 98.0, got %g", testexportsfresult);


    testexportresult = testXTLSXUb();

    printf("\nTesting XTLSXU, b Expected 0x4, got %x", testexportresult);


    testexportsfresult = testXTSSX();

    printf("\nTesting XTSSX, Expected 98.0, got %g", testexportsfresult);


    testexportsfresult = testXTSSXPa();

    printf("\nTesting XTSSXP, a Expected 98.0, got %g", testexportsfresult);


    testexportresult = testXTSSXPb();

    printf("\nTesting XTSSXP, b Expected 0x4, got %x", testexportresult);


    testexportsfresult = testXTSSXUa();

    printf("\nTesting XTSSXU, a Expected 98.0, got %g", testexportsfresult);


    testexportresult = testXTSSXUb();

    printf("\nTesting XTSSXU, b Expected 0x4, got %x", testexportresult);


    testexportresult = testXTUEQS();

    printf("\nTesting XTUEQ.S, Expected 0x4, got %x", testexportresult);


    testexportresult = testXTUEQSb();

    printf("\nTesting XTUEQ.S, b Expected 0x0, got %x", testexportresult);


    testexportresult = testXTUEQSc();

    printf("\nTesting XTUEQ.S, c Expected 0x0, got %x", testexportresult);


    testexportresult = testXTULES();

    printf("\nTesting XTULE.S, Expected 0x4, got %x", testexportresult);


    testexportresult = testXTULESb();

    printf("\nTesting XTULE.S, b Expected 0x4, got %x", testexportresult);


    testexportresult = testXTULESc();

    printf("\nTesting XTULE.S, c Expected 0x0, got %x", testexportresult);


    testexportresult = testXTULTS();

    printf("\nTesting XTULT.S, Expected 0x0, got %x", testexportresult);


    testexportresult = testXTULTSb();

    printf("\nTesting XTULT.S, b Expected 0x4, got %x", testexportresult);


    testexportresult = testXTULTSc();

    printf("\nTesting XTULT.S, c Expected 0x0, got %x", testexportresult);


    testexportresult = testXTUNSa();

    printf("\nTesting XTUN.S, a Expected 0x0, got %x", testexportresult);


    testexportresult = testXTUNSb();

    printf("\nTesting XTUN.S, b Expected 0x4, got %x", testexportresult);


    testexportresult = testXTUNSc();

    printf("\nTesting XTUN.S, c Expected 0x4, got %x", testexportresult);


    testexportresult = testXTSRA();

    printf("\nTesting XTSRA, Expected -0x2 (FFFFFFFE), got %x", testexportresult);


    testexportresult = testXTSRL();

    printf("\nTesting XTSRL, Expected 0x1FFFFFFE, got %x", testexportresult);


    testexportresult = testXTALL4a();

    printf("\nTesting XTALL4, a Expected 0x00, got %x", testexportresult);


    testexportresult = testXTALL4b();

    printf("\nTesting XTALL4, b Expected 0xF4, got %x", testexportresult);


    testexportresult = testXTALL4c();

    printf("\nTesting XTALL4, c Expected 0x70, got %x", testexportresult);


    testexportresult = testXTANY4a();

    printf("\nTesting XTANY4, a Expected 0x00, got %x", testexportresult);


    testexportresult = testXTANY4b();

    printf("\nTesting XTANY4, b Expected 0xF4, got %x", testexportresult);


    testexportresult = testXTANY4c();

    printf("\nTesting XTANY4, c Expected 0x74, got %x", testexportresult);


    testexportresult = testXTALL8a();

    printf("\nTesting XTALL8, a Expected 0x00, got %x", testexportresult);


    testexportresult = testXTALL8b();

    printf("\nTesting XTALL8, b Expected 0x1FF, got %x", testexportresult);


    testexportresult = testXTALL8c();

    printf("\nTesting XTALL8, c Expected 0x7F, got %x", testexportresult);


    testexportresult = testXTANY8a();

    printf("\nTesting XTALL8, a Expected 0x0, got %x", testexportresult);


    testexportresult = testXTANY8b();

    printf("\nTesting XTANY8, b Expected 0x1FF, got %x", testexportresult);


    testexportresult = testXTANY8c();

    printf("\nTesting XTANY8, c Expected 0x17F, got %x", testexportresult);


    testexportresult = testXTSSAIa();

    printf("\nTesting XTSSAI, a Expected 0x1F, got %x", testexportresult);


    testexportresult = testXTSSAIb();

    printf("\nTesting XTSSAI, b Expected 0x0, got %x", testexportresult);


    testexportresult = testXTMOVIN();

    printf("\nTesting XTMOVI.N, Expected 0x43, got %x", testexportresult);


    testexportresult = testXTBFa();

    printf("\nTesting XTBF, a Expected 0x0, got %x", testexportresult);


    testexportresult = testXTBFb();

    printf("\nTesting XTBF, b Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBTa();

    printf("\nTesting XTBT, a Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBTb();

    printf("\nTesting XTBT, b Expected 0x8, got %x", testexportresult);


    testexportresult = testXTBALLa();

    printf("\nTesting XTBALL, a Expected 0x35, got %x", testexportresult);


    testexportresult = testXTBALLb();

    printf("\nTesting XTBALL, b Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBALLc();

    printf("\nTesting XTBALL, c Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBANYa();

    printf("\nTesting XTBANY, a Expected 0x35, got %x", testexportresult);


    testexportresult = testXTBANYb();

    printf("\nTesting XTBANY, b Expected 0x34, got %x", testexportresult);


    testexportresult = testXTBANYc();

    printf("\nTesting XTBANY, c Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBBCa();

    printf("\nTesting XTBBC, a Expected 0x05, got %x", testexportresult);


    testexportresult = testXTBBCb();

    printf("\nTesting XTBBC, b Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBBSa();

    printf("\nTesting XTBBS, a Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBBSb();

    printf("\nTesting XTBBS, b Expected 0x15, got %x", testexportresult);


    testexportresult = testXTBGEU();

    printf("\nTesting XTBGEU, Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBGEUb();

    printf("\nTesting XTBGEU, b Expected -0x1, got %x", testexportresult);


    testexportresult = testXTBGEUc();

    printf("\nTesting XTBGEU, c Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNALLa();

    printf("\nTesting XTBNALL, a Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNALLb();

    printf("\nTesting XTBNALL, b Expected 0x34, got %x", testexportresult);


    testexportresult = testXTBNALLc();

    printf("\nTesting XTBNALL, c Expected 0x10, got %x", testexportresult);


    testexportresult = testXTBNONEa();

    printf("\nTesting XTBNONE, a Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNONEb();

    printf("\nTesting XTBNONE, b Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNONEc();

    printf("\nTesting XTBNONE, c Expected 0x10, got %x", testexportresult);


    testexportsfresult = testXTABSS();

    printf("\nTesting XTABS.S, Expected 2.0, got %g", testexportsfresult);


    testexportsfresult = testXTNEGS();

    printf("\nTesting XTNEG.S, Expected -2.0, got %g", testexportsfresult);


    testexportresult = testXTNSA();

    printf("\nTesting XTNSA, Expected 0x1E, got %x", testexportresult);


    testexportresult = testXTNSAU();

    printf("\nTesting XTNSAU, Expected 0x1F, got %x", testexportresult);


    testexportsfresult = testXTADDEXPS();

    printf("\nTesting ADDEXP.S, Expected 8.0, got %g", testexportsfresult);


    testexportsfresult = testXTADDEXPMS();

    printf("\nTesting XTADDEXPM.S, Expected 16.0, got %g", testexportsfresult);


    testexportsfresult = testXTCONSTS();

    printf("\nTesting XTCONST.S, Expected 0.5, got %g", testexportsfresult);


    testexportsfresult = testXTRECIP0S();

    printf("\nTesting XTRECIP0.S, Expected 1/64, got %g", testexportsfresult);


    testexportresult = testXTEXTUI();

    printf("\nTesting XTEXTUI, Expected 0x3C, got %x", testexportresult);


    testexportresult = testXTSRAI();

    printf("\nTesting XTSRAI, Expected 0xFFFFFFF0, got %x", testexportresult);


    testexportresult = testXTMOVSP();

    printf("\nTesting XTMOVSP, Expected 0xFFFFFF00, got %x", testexportresult);


    testexportresult = testXTBEQZNa();

    printf("\nTesting XTBEQZ.N, eq case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBEQZNb();

    printf("\nTesting XTBEQZ.N, ne b case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBEQZNc();

    printf("\nTesting XTBEQZ.N, ne c case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNEZNa();

    printf("\nTesting XTBNEZ.N, = case: Expected 0x11, got %x", testexportresult);


    testexportresult = testXTBNEZNb();

    printf("\nTesting XTBNEZ.N, > b case: Expected 0x31, got %x", testexportresult);


    testexportresult = testXTBNEZNc();

    printf("\nTesting XTBNEZ.N, < c case: Expected 0x31, got %x", testexportresult);


    testexportresult = testEQZIFa();

    printf("\nTesting EQZ IF, a ==0 case: Expected 0x31, got %x", testexportresult);


    testexportresult = testEQZIFb();

    printf("\nTesting EQZ IF, b <>0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testELSEa();

    printf("\nTesting ELSE, a ==0 case: Expected 0x29, got %x", testexportresult);


    testexportresult = testELSEb();

    printf("\nTesting EQZ IF, b <>0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testEQZUNTIL();

    printf("\nTesting EQZ UNTIL, Expected 0x10, got %x", testexportresult);


    testexportresult = testNEZWHILEREPEAT();

    printf("\nTesting NEZ WHILE, REPEAT, Expected 0x0E, got %x", testexportresult);


    testexportresult = testNEZIFa();

    printf("\nTesting NEZ IF, a ==0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testNEZIFb();

    printf("\nTesting NEZ IF, b <>0 case: Expected 0x31, got %x", testexportresult);


    testexportresult = testNEIFa();

    printf("\nTesting NE IF, a ==0 case: Expected 0x31, got %x", testexportresult);


    testexportresult = testNEIFb();

    printf("\nTesting NE IF, b <>0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testBITFIFa();

    printf("\nTesting BITF IF, a ==0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testBITFIFb();

    printf("\nTesting BITF IF, b <>0 case: Expected 0x08, got %x", testexportresult);


    testexportresult = testBITTIFa();

    printf("\nTesting BITT IF, a ==0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testBITTIFb();

    printf("\nTesting BITT IF, b <>0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testLTIFa();

    printf("\nTesting LT IF, -1 < 0 case: Expected 0x11, got %x", testexportresult);

    
    testexportresult = testLTIFb();

    printf("\nTesting LT IF, 0 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testLTIFc();

    printf("\nTesting LT IF, 1 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testGEIFa();

    printf("\nTesting GE IF, -1 < 0 case: Expected 0x00, got %x", testexportresult);

    
    testexportresult = testGEIFb();

    printf("\nTesting GE IF, 0 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testGEIFc();

    printf("\nTesting GE IF, 1 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testLTUIFa();

    printf("\nTesting LTU IF, -1 < 0 case: Expected 0x00, got %x", testexportresult);

    
    testexportresult = testLTUIFb();

    printf("\nTesting LTU IF, 0 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testLTUIFc();

    printf("\nTesting LTU IF, 1 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testLTUIFd();

    printf("\nTesting LTU IF, 0 < 1 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testGEUIFa();

    printf("\nTesting GEU IF, -1 < 0 case: Expected 0x11, got %x", testexportresult);

    
    testexportresult = testGEUIFb();

    printf("\nTesting GEU IF, 0 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testGEUIFc();

    printf("\nTesting GEU IF, 1 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testGEUIFd();

    printf("\nTesting GEU IF, 0 < 1 case: Expected 0x00, got %x", testexportresult);



    testexportresult = testLEIFa();

    printf("\nTesting LE IF, -1 < 0 case: Expected 0x11, got %x", testexportresult);

    
    testexportresult = testLEIFb();

    printf("\nTesting LE IF, 0 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testLEIFc();

    printf("\nTesting LE IF, 1 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testGTIFa();

    printf("\nTesting GT IF, -1 < 0 case: Expected 0x00, got %x", testexportresult);

    
    testexportresult = testGTIFb();

    printf("\nTesting GT IF, 0 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testGTIFc();

    printf("\nTesting GT IF, 1 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testLEUIFa();

    printf("\nTesting LEU IF, -1 < 0 case: Expected 0x00, got %x", testexportresult);

    
    testexportresult = testLEUIFb();

    printf("\nTesting LEU IF, 0 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testLEUIFc();

    printf("\nTesting LEU IF, 1 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testLEUIFd();

    printf("\nTesting LEU IF, 0 < 1 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testGTUIFa();

    printf("\nTesting GTU IF, -1 < 0 case: Expected 0x11, got %x", testexportresult);

    
    testexportresult = testGTUIFb();

    printf("\nTesting GTU IF, 0 < 0 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testGTUIFc();

    printf("\nTesting GTU IF, 1 < 0 case: Expected 0x11, got %x", testexportresult);


    testexportresult = testGTUIFd();

    printf("\nTesting GTU IF, 0 < 1 case: Expected 0x00, got %x", testexportresult);


    testexportresult = testXTL8UIa();

    printf("\nTesting XTL8UI: Expected 0x89, got %x", testexportresult);


    testexportresult = testXTL8UIb();

    printf("\nTesting XTL8UI: Expected 0x07, got %x", testexportresult);


    testexportresult = testXTL16SIa();

    printf("\nTesting XTL16SI case a: Expected 0xFFFF8141, got %x", testexportresult);


    testexportresult = testXTL16SIb();

    printf("\nTesting XTL16SI case b: Expected 0x1121, got %x", testexportresult);


    testexportresult = testXTL16UIa();

    printf("\nTesting XTL16UI case a: Expected 0x8141, got %x", testexportresult);


    testexportresult = testXTL16UIb();

    printf("\nTesting XTL16UI case b: Expected 0x1121, got %x", testexportresult);


    testexportsfresult = testXTLSI();

    printf("\nTesting XTLSI, Expected 2.0, got %g", testexportsfresult);


    testexportsfresult = testXTLSIPa();

    printf("\nTesting XTLSIP, case a: Expected 2.0, got %g", testexportsfresult);


    testexportresult = testXTLSIPb();

    printf("\nTesting XTLSIP case b: Expected 0x4, got %x", testexportresult);


    // testexportsfresult = testXTLSIUa();

    // printf("\nTesting XTLSIU, case a: Expected 2.0, got %g", testexportsfresult);


    // testexportresult = testXTLSIUb();

    // printf("\nTesting XTLSIU case b: Expected 0x4, got %x", testexportresult);


    testexportresult = testXTS8I();

    printf("\nTesting XTS8I: Expected 0x89000000, got %x", testexportresult);


    testexportresult = testXTS16I();

    printf("\nTesting XTS16I: Expected 0x07890000, got %x", testexportresult);


    testexportsfresult = testXTSSIPa();

    printf("\nTesting XTSSIP, case a: Expected -9.0, got %g", testexportsfresult);


    testexportresult = testXTSSIPb();

    printf("\nTesting XTSSIP case b: Expected 0x4, got %x", testexportresult);


    testexportresult = testN32toAR();

    printf("\nTesting testN32>AR,: Expected 0x23974982, got %x", testexportresult);


    testexportresult = testNtoARa();

    printf("\nTesting testN>ARa,: Expected 0x0, got %x", testexportresult);


    testexportresult = testNtoARb();

    printf("\nTesting testN>ARb,: Expected 0x60, got %x", testexportresult);


    testexportresult = testNtoARc();

    printf("\nTesting testN>ARc,: Expected 0x800, got %x", testexportresult);


    testexportresult = testU8bracketARtoAR();

    printf("\nTesting testU8[AR]->AR,: Expected 0x34, got %x", testexportresult);


    testexportresult = testU16bracketARtoAR();

    printf("\nTesting testU16[AR]->AR,: Expected 0x8234, got %x", testexportresult);


    testexportresult = testN16bracketARtoAR();

    printf("\nTesting testN16[AR]->AR,: Expected 0xFFFF8234, got %x", testexportresult);


    testexportresult = testARtoU8bracketAR();

    printf("\nTesting testAR->U8[AR],: Expected 0x34, got %x", testexportresult);


    testexportresult = testARtoU16bracketAR();

    printf("\nTesting testAR->U16[AR],: Expected 0x8234, got %x", testexportresult);


    testexportresult = testARplusNtoARa();

    printf("\nTesting testAR+N->AR, case a: Expected 0x234, got %x", testexportresult);


    testexportresult = testARplusNtoARb();

    printf("\nTesting testAR+N->AR, case b: Expected 0x244, got %x", testexportresult);


    testexportresult = testARplusNtoARc();

    printf("\nTesting testAR+N->AR, case c: Expected 0x235, got %x", testexportresult);


    testexportresult = testARplusNtoARd();

    printf("\nTesting testAR+N->AR, case d: Expected 0x245, got %x", testexportresult);


    testexportresult = testARplusNtoARe();

    printf("\nTesting testAR+N->AR, case e: Expected 0x2B4, got %x", testexportresult);


    testexportresult = testARplusNtoARf();

    printf("\nTesting testAR+N->AR, case f: Expected 0x2B5, got %x", testexportresult);


    testexportresult = testARplusNtoARg();

    printf("\nTesting testAR+N->AR, case g: Expected 0x235, got %x", testexportresult);


    testexportresult = testARplusNtoARh();

    printf("\nTesting testAR+N->AR, case h: Expected 0x234, got %x", testexportresult);


    testexportresult = testARplusNtoARi();

    printf("\nTesting testAR+N->AR, case i: Expected 0x2B5, got %x", testexportresult);


    testexportresult = testBracketOtoARa();

    printf("\nTesting test[O]->AR, case a: Expected 0x18936385, got %x", testexportresult);


    testexportresult = testBracketOtoARb();

    printf("\nTesting test[O]->AR, case b: Expected 0x18936385, got %x", testexportresult);


    testexportresult = testBracketOtoARc();

    printf("\nTesting test[O]->AR, case c: Expected 0x18936385, got %x", testexportresult);


    testexportresult = testBracketOtoARd();

    printf("\nTesting test[O]->AR, case d: Expected 0x18936385, got %x", testexportresult);


    testexportresult = testBracketOtoARe();

    printf("\nTesting test[O]->AR, case e: Expected 0x18936385, got %x", testexportresult);


    printf("\n");


    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
