// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DG6502CrossAsm v1.2
//
//    DG6502CrossAsm v1.2 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DG6502CrossAsm v1.2 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DG6502CrossAsm v1.2; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 25, 2023              //
// version 1.2                //
// /////////////////////////////


DiaperGlu 6502 Cross Assembler


To load the assembler or disassembler, do this:

  copy diaperglu or nodiaperglu to the folder containing DG6502CrossAsm.dglu

  open a terminal

  cd to the directory containing DG6502CrossAsm.dglu

  on Mac do ./diaperglu or ./nodiaperglu 

  on Windows do diaperglu or nodiaperglu

  if you want to do assembly, from the OK> command prompt do:
    $" DG6502CrossAsm.dglu" INCLUDEFILE$

  if you want to do disassembly, from the OK> command prompt do:
    $" DG6502DisAsm.dglu" INCLUDEFILE$

  if you want to do BOTH assembly and disassembly I recommend loading both of them before
    you do any assembly since INCLUDEFILE$ loads to the current compile buffer and will
    add to the last thing you assembled unless you manually change the value in
    PCURRENTCOMPILEBUFFER yourself. 
  

Some things to consider:

  This assembler supports the 65C02 additional instructions.
 
  If you are using it to compile regular 6502 code, you will not get an error if you feed 
    it a 65C02 instruction.

  This assembler compiles onto the end of the current compile buffer. 
    PCURRENTCOMPILEBUFFER holds the buffer id of the current compile buffer.

  This compiler uses standard math array notation for the addressing modes. Hopefully this
    makes it easier for people to learn and remember.

  This is a standard Forth assembler. The data for the instruction comes in reverse order
    before the opcode. 

  The format for most instructions is data addressingmode opcode,

  The addressingmode is required. 
    It is possible to modify the assembler to assume an addressingmode if it is missing, 
      but then it wouldn't have the same format as the existing x86 assembler.
    In the x86 assembler, registers are the default mode. In this assembler, the registers
      are just addressing modes.

  CC is a valid Forth hexadecimal number. For this reason I did not name the carry 
    clear condition code CC. Instead I named it NC even though the branch is called BCC, 
    If your control flow stuff isn't compiling correctly it may be because you used CC 
    instead of NC.

  A is a valid Forth hexadecimal number. For this reason I used RA as the name of 
    register A.

  DiaperGlu has more advanced words than CONSTANT for handling assembler symbols. If you 
    need to group symbols or have hierarchical symbols, check out DiaperGlu's hierarchical 
    list stuff and the EH stack. 


To start assembling, do this:

  Use NEWCROSSBUFFER ( baseaddress -- ) to make a new buffer, set it as the current compile 
    buffer, and set the base address of the data in the buffer.

  For example:

    HEX 
    2000 NEWCROSSBUFFER  

    You now have a new empty buffer.  PBASEADDRESS  holds the current base address of the 
      data in the buffer and will hold the value 2000 at this point.

  Now start compiling your 6502 code. The format for most 6502 instructions is:
    data addressingmode opcode,

  For example:

    HEX
    72 U8 LDA,

    You now have a buffer with 2 bytes in it. The first byte at offset 0 is A9, and the 
      second at offset 1 is 72 

  If you want to see a dump of the buffer use .CROSSBUFFER ( -- )

  If you want to make a symbol relative to the base address, one way is to use
    BARHERE ( -- baraddress ) and 
    ( value -- ) CONSTANT ( "word<space>morestuff" -tib- "morestuff" ) 

  For example:

    BARHERE CONSTANT mysubstart

    You now have a constant with the value 2002.


To save your compiled code to a file, do this:

  PCURRENTCOMPILEBUFFER @ $" myfilename.bin" SAVEFILE$

  If it worked, you now have a file named myfilename.bin containing the entire contents 
    of the current compile buffer which at this point is A9 72
  

The test script should have an example of each addressingmode opcode, combination in it.


// //////////////////////////////////////////////////////////////////////// 


Addressing Modes: ( -- addrmode )

  Register targets          RA  X  Y
  Immediate targets         U8  U16
  Direct Memory targets     [U8] [U16]  [U8+X] [U16+X]  [U8+Y] [U16+Y]
  Indirect Memory targets   [[U8+X]]  [[U8]+Y]
  PC relative               PC+N8


// ////////////////////////////////////////////////////////////////////////


One target instructions: ( data addrmode -- ) 

  ORA,  AND,  EOR,  ADC,  STA,  LDA,  CMP,  SBC,  
  STZ,  
  ASL,  ROL,  LSR,  ROR, 
  TRB,  TSB,  
  JSR,  BIT,  JMP,  
  STY,  STX,  LDX,  LDY,  
  CPY,  CPX,  INC,  DEC,  
  PUSH, PULL, 


For example:

  HEX  
  76 U8 LDA,  
  1002 [U16] STA,
  RA ASL,


Note:

  You always need to specify the addressing mode.


// ////////////////////////////////////////////////////////////////////////


No target instructions: ( -- )

  BRK,  RTI,  RTS,  PHP,  CLC,  PLP,  SEC,  PHA,
  CLI,  PLA,  SEI,  CLV,  CLD,  NOP,  SED,  TAX, 
  TAY,  TSX,  TXA,  TXS,  TYA,  INY,  DEX,  INX, 
  DEY,  DEA,  INA,  PHX,  PHY,  PLY, 


For example:

  RTS,


// ////////////////////////////////////////////////////////////////////////


Condition codes: ( -- cc )

  ALWAYS  MI  PL  VC  VS  NC  CS  NE  EQ  NEVER  NZ  ZS


Forth style control flow instructions:

  These instructions compile short branches. 
  Except for UNTIL, the branch distance must be from -80 to 7F
  UNTIL, will compile a long branch if needed
  ELSE, REPEAT, and LONGREPEAT, use CLC, NC UNTIL, for their branches which means
    they clear the carry flag
  QELSE, and QREPEAT, use BRA, which is not available in the original version of 
    the 6502

  ( cc -- ) IF, THEN,
  ( cc -- ) IF, ELSE, THEN,
  ( cc -- ) IF, QELSE, THEN,

  BEGIN, ( cc -- ) UNTIL,           

  BEGIN, ( cc -- ) WHILE, REPEAT,   
  BEGIN, ( cc -- ) WHILE, QREPEAT,  
  
  // these compile a branch over a jump, so there is no limit on the branch distance 
  ( cc -- ) LONGIF, LONGTHEN,              
  ( cc -- ) LONGIF, LONGELSE, LONGTHEN,

  BEGIN, ( cc -- ) LONGWHILE, LONGREPEAT,


For example:

  // counts down from 5
  5 U8 LDX,
  BEGIN,  
    // do something while X U> 0, so for X = 5, 4, 3, 2, and 1
    DEX,
  EQ UNTIL,

  // checks if register A is 8
  8 U8 CMP,
  EQ IF,
    // do something
  THEN,

  // checks if register A U>= 3
  3 U8 CMP,
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

  
Branch instructions: ( branchtarget addrmode -- )

  BMI,  BPL,  
  BVC,  BVS,  
  BCC,  BNC,  BCS,  
  BNE,  BEQ, 
  BRA,  BNEVER, 


For example:

  HEX -18 PC+N8 BMI,  // compiles a backwards branch relative to the address
                      //   after this instruction

  HEX FAD8 U16 BPL,   // compiles a branch to address FAD8


Note:

  It might be simpler to use the Forth style control flow instructions.

  Except for BRA, and BNEVER, if the branch distance is not in the range of -80 to 7F
    these branch instructions compile a long branch. A long branch is a branch of the
    opposite condition over a jump instruction.
    

  If BRA, is too far for a short branch, a JMP, is compiled. If you used PC+N8
    with BRA, and it is too far for a short branch, the start of the instruction + 2
    is used as the after branch offset of the branch.

  BNEVER, does not compile anything.


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
 

DiaperGlu 6502 Disassembler


PDISASMBASEADDRESS  
  // holds the buffer's relative base address for the disassembler


DISASM>NEW$ ( offset bufferid length -- ) ( -$- disasm$ )  
  // disassembles a segment of the buffer


For example, if you have buffer with 6502 code it it,

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
  0 mybufid -1 DISASM>NEW$
  .$

  

    