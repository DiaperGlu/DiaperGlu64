// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DG68HC11CrossAsm v1.0
//
//    DG68HC11CrossAsm v1.0 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DG68HC11CrossAsm v1.0 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DG68HC11CrossAsm v1.0; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 23, 2023              //
// version 1.0                //
// /////////////////////////////


DiaperGlu 68HC11 Cross Assembler


To load the assembler or disassembler, do this:

  copy diaperglu or nodiaperglu to the folder containing DG68HC11CrossAsm.dglu

  open a terminal

  cd to the directory containing DG68HC11CrossAsm.dglu

  on Mac do ./diaperglu or ./nodiaperglu 

  on Windows do diaperglu or nodiaperglu

  if you want to do assembly, from the OK> command prompt do:
    $" DG68HC11CrossAsm.dglu" INCLUDEFILE$

  if you want to do disassembly, from the OK> command prompt do:
    $" DG68HC11DisAsm.dglu" INCLUDEFILE$

  if you want to do BOTH assembly and disassembly I recommend loading both of them before
    you do any assembly since INCLUDEFILE$ loads to the current compile buffer and will
    add to the last thing you assembled unless you manually change the value in
    PCURRENTCOMPILEBUFFER yourself. 
  

Some things to consider:

  This assembler compiles onto the end of the current compile buffer. 
    PCURRENTCOMPILEBUFFER holds the buffer id of the current compile buffer.

  This compiler uses standard math array notation for the addressing modes. Hopefully this
    makes it easier for people to learn and remember.

  This is a standard Forth assembler. The data for the instructions come in reverse order
    before the opcodes. 

  The format for most instructions is data addressingmode opcode,

  Except for the bit mask in instructions like BSET, the addressingmode is required. 
    It is possible to modify the assembler to assume an addressingmode if it is missing, 
      but then it wouldn't have the same format as the existing x86 assembler.
    In the x86 assembler, registers are the default mode. In this assembler, the registers
      are just addressing modes.

  CC is a valid Forth hexadecimal number. For this reason I did not name the carry 
    clear condition code CC. Instead I named it NC even though the branch is called BCC, 
    If your control flow stuff isn't compiling correctly it may be because you used CC 
    instead of NC.

  A and B are valid Forth hexadecimal numbers. For this reason I used RA and RB as the
    names of registers A and B.

  DiaperGlu has more advanced words than CONSTANT for handling assembler symbols. If you 
    need to group symbols or have hierarchical symbols, check out DiaperGlu's hierarchical 
    list stuff and the EH stack.
  
  The test assembles, disassembles, and reassembles almost every instruction and addressing mode. 

  The disassembler generated source code will reassemble into the exact same object code.
    The test verifies that you can do this.

  I did not test the compiled code with an HC11 machine yet. I may have missed something.
    If there is something I missed, it is probably in one of the convenience instructions
    that compile into multiple opcodes like PUSHD, PULD, RORD, or ROLD, I may have these
    backwards... ( 24 Jun 2023 v1.0 )

  The assembler supports Forth style control flow which eliminates the need for many branch
    target symbols. ( see Forth style control flow instructions section below )

  The assembler also supports traditional branches using the standard branch instruction 
    names.

  The assembler also supports long branches using a short relative branch in combination
    with an absolute jump. If the branch target is known, the assembler will compile a 
    long branch if it is needed. 
  

To start assembling, do this:

  Use NEWCROSSBUFFER ( baseaddress -- ) to make a new buffer, set it as the current compile 
    buffer, and set the base address of the data in the buffer.

  For example:

    HEX 
    2000 NEWCROSSBUFFER  

    You now have a new empty buffer.  PBASEADDRESS  holds the current base address of the 
      data in the buffer and will hold the value 2000 at this point.

  Now start compiling your 68HC11 code. The format for most 68HC11 instructions is:
    data addressingmode opcode,

  For example:

    HEX
    72 U8 LDAA,

    You now have a buffer with 2 bytes in it. The first byte at offset 0 is 86, and the 
      second at offset 1 is 72 

  If you want to see a dump of the buffer use .CROSSBUFFER ( -- )

  If you want to make a symbol relative to the base address, one way is to use
    BARHERE ( -- baraddress ) and 
    ( value -- ) CONSTANT ( "word<space>morestuff" -tib- "morestuff" ) 

  For example:

    BARHERE CONSTANT mysubstart

    You now have a constant with the value 2002.

  If you want to see examples of just about every instruction being used, look at 
    TestDG68HC11CrossAsm.dglu


To save your compiled code to a file, do this:

  PCURRENTCOMPILEBUFFER @ $" myfilename.bin" SAVEFILE$

  If it worked, you now have a file named myfilename.bin containing the entire contents 
    of the current compile buffer which at this point is A9 72
  

The test script should have an example of each addressingmode opcode, combination in it.


// //////////////////////////////////////////////////////////////////////// 


Addressing Modes: ( -- addrmode )

  Register targets          RA  RB  X  Y
  Immediate targets         U8  U16
  Direct Memory targets     [U8] [U16]  [U8+X] [U8+Y] 
  PC relative               PC+N8


// ////////////////////////////////////////////////////////////////////////


One target instructions: ( data addrmode -- ) 

ADCA,  
ADCB, 
ADDA,  
ADDB,  
ADDD,  
ANDA,  
ANDB,  
ASL,   
ASR,   
BITA,  
BITB,  
CLR,
CMPA,
CMPB,
COM,
CPD,
CPX,
CPY,
DEC,
EORA,
EORB,
INC,
JMP,
JMPEA,
JSR,
JSREA,
LDAA,
LDAB,
LDD,
LDS,
LDX,
LDY,
LSL,
LSR,
NEG,
ORAA,
ORAB,
PUSH,
PULL,
ROL,
ROR,
SBCA,
SBCB,
STAA,
STAB,
STD,
STS,
STX,
STY,
SUBA,
SUBB,
SUBD,
TST, 


For example:

  HEX  
  76 U8 LDAA,  
  1002 [U16] STAA,
  RA ASL,


Note:

  You always need to specify the addressing mode for these instructions.


// ////////////////////////////////////////////////////////////////////////

Two target instructions: ( u8mask data addressingmode -- )

BCLR,
BSET,

Note:

  You do not specify the u8mask's addressing mode for these instructions, the
    mask is always an unsigned 8 bit integer.
  You must specify the data's addressing mode for these instructions.

// ////////////////////////////////////////////////////////////////////////


No target instructions: ( -- )

ABA,
ABX,
ABY,
CBA,
CLC,
CLI,
COMA,
COMB,
DAA,
DECA,
DECB,
DES,
DEX,
DEY,
INCA,
INCB,
INS,
INX,
INY,
LSLA,
LSLB,
LSLD,
LSRA,
LSRB,
LSRD,
MUL,
NEGA,
NEGB,
NOP,
PSHA,
PSHB,
PSHD,
PSHX,
PSHY,
PULA,
PULB,
PULD,
PULX,
PULY,
ROLA,
ROLB,
ROLD,
RORA,
RORB,
RORD,
RTI,
RTS,
SBA,
SEC,
SEI,
SEV,
STOP,
SWI,
TAB,
TAP,
TBA,
TEST,
TPA,
TSTA,
TSTB,
TSX,
TSY,
TXS,
TYS,
WAI,
XGDX,
XGDY,


For example:

  RTS,


// ////////////////////////////////////////////////////////////////////////


Condition codes: ( -- cc )

ALWAYS
MI
PL
VC
VS
NC 
CS
NE
EQ
NEVER
GE
GT
HI
HS
LE
LO
LS
LT
NSET
NMASKEDSET
SET
MASKEDSET
NCLR
NMASKEDCLR
CLR
MASKEDCLR
NZ
ZS


Forth style control flow instructions:

  These instructions compile short branches. 
  Except for UNTIL, the branch distance must be from -80 to 7F
  UNTIL, will compile a long branch if needed

  ( cc -- ) or ( mask u8addr maskaddrmode cc -- ) IF, THEN,
  ( cc -- ) or ( mask u8addr maskaddrmode cc -- ) IF, ELSE, THEN,

  BEGIN, ( cc -- ) or ( mask u8addr maskaddrmode cc -- )  UNTIL,           

  BEGIN, ( cc -- ) or ( mask u8addr maskaddrmode cc -- ) WHILE, REPEAT,     
  
  // these compile a branch over a jump, so there is no limit on the branch distance 
  ( cc -- ) or ( mask u8addr maskaddrmode cc -- ) LONGIF, LONGTHEN,              
  ( cc -- ) or ( mask u8addr maskaddrmode cc -- ) LONGIF, LONGELSE, LONGTHEN,

  BEGIN, ( cc -- ) or ( mask u8addr maskaddrmode cc -- ) LONGWHILE, LONGREPEAT,


For example:

  // counts down from 5
  5 U8 LDX,
  BEGIN,  
    // do something while X U> 0, so for X = 5, 4, 3, 2, and 1
    DEX,
  EQ UNTIL,

  // checks if register A is 8
  8 U8 CMPA,
  EQ IF,
    // do something
  THEN,

  // checks if register A U>= 3
  3 U8 CMPA,
  NC IF, 
    // do something if A U>= 3
  ELSE,
    // do something else if A U< 3 
  THEN,

  // another count down loop
  5 U8 LDX,
  BEGIN,
    DEX,
  NE WHILE,
    // do something while X U> 0, so for x = 4, 3, 2, and 1
  REPEAT,


// ////////////////////////////////////////////////////////////////////////


Branch addressing modes: ( -- addrmode )

  U16  PC+N8

  
One target branch instructions: ( branchtarget branchaddrmode -- )

BRA,
BMI,
BPL,
BVC,
BVS,
BCC,
BNC,
BCS,
BNE,
BEQ,
BRN,
BGE,
BGT,
BHI,
BHS,
BLE,
BLO,
BLS,
BLT,
BSR,


For example:

  HEX -18 PC+N8 BMI,  // compiles a backwards branch relative to the address
                      //   after this instruction

  HEX FAD8 U16 BPL,   // compiles a branch to address FAD8



Three target branch instructions: ( mask u8addr maskaddrmode branchtarget branchaddrmode -- )

BRSET,
BRNSET,
BRCLR,
BRNCLR,


Note:

  It might be simpler to use the Forth style control flow instructions.

  If the branch distance is not in the range of -80 to 7F
    these branch instructions compile a long branch. A long branch is a branch of the
    opposite condition over a jump instruction.
    

  If BRA, is too far for a short branch, a JMP, is compiled.

// ////////////////////////////////////////////////////////////////////////


Labels a.k.a. symbols:

  There are a lot of ways to make a symbol. Perhaps the simplest is to use CONSTANT

For example:

  HEX D20A CONSTANT Random


To get the current compile address use BARHERE

For example:
 
  BARHERE CONSTANT MyAdd20Sub

    HEX 20 U8 ADD,
    RTS,


// ////////////////////////////////////////////////////////////////////////
// ////////////////////////////////////////////////////////////////////////
 

DiaperGlu 68HC11 Disassembler


PDISASMBASEADDRESS  
  // holds the buffer's relative base address for the disassembler


DISASM>NEW$ ( offset bufferid length -- ) ( -$- disasm$ )  
  // disassembles a segment of the buffer


For example, if you have buffer with 68HC11 code it it,

  First you put the base address of the buffer into PDISASMBASEADDRESS
 
  then you put the start offset of the code in the buffer onto the data stack,
    ( a start offset of 0 means you want to start at the beginning of the buffer )

  then you put the buffer id of the buffer on the data stack,
  then you put the length of the code you want to disassemble onto the data stack
    ( a length of -1 means do the whole buffer )

  then you do DISASM>NEW$

  then you can do .$ to see the disassembled code.


For example:

  If you did: 

    HEX 
    2000 NEWCROSSBUFFER
    D20A [U16] LDA,
    20 U8 CMP,
    NC IF, 
      8000 [U16] STA,
    THEN,
    RTS,

  You can see the disassembled code with this:

    2000 PDISASMBASEADDRESS !
    0 PCURRENTCOMPILEBUFFER @ -1 DISASM>NEW$
    .$


To disassemble a previously saved file, do this:

  $" myfilename.bin" LOADFILE$ CONSTANT mybufid
  2000 PDISASMBASEADDRESS !
  0 mybufid -1 DISASM>NEW$
  .$

  

    