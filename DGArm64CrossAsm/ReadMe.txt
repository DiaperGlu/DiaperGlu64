
Welcome to the DiaperGlu Cross Assembler for Arm64 version 0.8.
Friday Jan 23, 2026


Document key:

  IR          = integer register
  IR64        = a 64 bit integer register
  R           = an integer register
  X0          = Arm64 64 bit integer register X0
  Xn          = Arm64 64 bit integer register Xn where n is 0 through 31
  [IR64]      = value in memory using the value in IR as the address

  n or N      = 64 bit signed integer
  u or U      = 64 bit unsigned integer
  n8 or N8    = signed 8 bit integer
  u8 or U8    = unsigned 8 bit integer
  n16 or N16  = signed 16 bit integer
  u16 or U16  = unsigned 16 bit integer
  n24 or N24  = signed 24 bit integer
  u24 or U24  = unsigned 24 bit integer
  n32 or N32  = signed 32 bit integer
  u32 or U32  = unsigned 32 bit integer
  n64 or N64  = 64 bit integer
  u64 or U64  = 64 bit integer  
              =  in general u U n or N followed by a number is an integer with that many bits

  O           = 0 based offset in bytes from start of the current compile buffer
  [O]         = value in the current compile buffer at 0 based offset O  

  ->          = copy the left value to the right value
  ,           = a comma at the end of a forth script word means it compiles something to the
              current compile buffer 


This cross assembler has a few script files that run under DiaperGlu on Arm64 Mac.

    - DiaperGlu is available from https://github.com/DiaperGlu/DiaperGlu64

    - Due to modern OS security restrictions, you need to build DiaperGlu from source. 

    - the docs are in the /docs folder. index.htm is the root doc. building.htm has the build instructions.

    - After building DiaperGlu, the simplest thing to do is copy the stand alone executable to
      the directory holding this ReadMe.txt file.


The script files included in this project:

  1) DGArm64CrossAsm.dglu is a Forth assembler for the 64 bit Arm processor.

    - Just in case you don't know what a cross assembler is, this assembler executes
      compiling words like ARMADDEXTENDED, to compile source code into raw Arm64 object code.

    - This assembler uses a few DiaperGlu specific words, but it should be
      relatively easy to port it to another Forth.

    - This assembler has words that compile multiple instructions. These words may
      trash the two user defined scratch registers SCRATCHREG1 and SCRATCHREG2. I chose
      the default scratch registers to be the ones Mac OS might trash during the preamble
      of a subroutine call, or during a long branch.

    - Almost all the basic Arm64 instructions are available but most do not work the
      same way as the Arm64 assembler. The reasons for changing how they work
      were to simplify things, make them easier to remember, and to avoid name
      conflicts with hexadecimal numbers. To be more specific:

        - only instructions from the basic instruction set are available at this time

        - Arm64 instructions are prefaced with ARM and have a comma after them.
          For example NOP becomes ARMNOP, although I did also define a convenience word
          named NOP,

        - The parameters for the instructions are not in the same order. To
          make it easier to remember, I tried to use the Forth standard ordering.
          This means sources come before destinations, and for instructions where
          the order of the sources matter, like ARMSUBIMMEDIATE, the Forth standard 
          ordering is used. So if you say HEX X3 37 0 X4 64BIT ARMSUBIMMEDIATE, 
          it means X3 - (0x37 << 0) -> X4. There were a couple instructions where I
          wasn't sure what to do. But since this is Forth, it is very easy to change
          things if you would prefer something else. That's the beauty of Forth.

    - I tried to test in a way that covered most of the user mode instructions. While
      doing so I kept finding bugs... so I'm pretty sure there are bugs in the stuff
      I didn't test. Even with the stuff I did test, more testing is needed. Also,
      I tested that instructions that update flags really update the flags, but I
      did not test that preserve flags instructions really preserve the flags.

    - This assembler compiles to the current compile buffer.

      - I recommend allocating a separate buffer and making it the current compile
        buffer. On Diaperglu, the commands to do this are:

          HEX 1000 -1 NEWBUFFER CONSTANT mybuffername
          mybuffername PCURRENTCOMPILEBUFFER !

        or if you are going to use the .o maker script then this will do the above in one step:

          NEW-FLAT-OSYMBOL-BUF

      - Once you have compiled the code into a buffer, you have to get it to where
        you need it to go. DiaperGlu has a command to save a buffer to a file
        if that helps. It looks like this:

          mybuffername $" myfilename" SAVEFILE$

        This project also comes with a script that can convert a buffer to a
        Macho compatible .o file. This script is documented later in this file.

    - This assembler supports setting a non zero base address, but I did not test
      the non zero case yet, and if you are making a .o file you should leave
      the base address as 0. But if you want to change it, do this:

        HEX mynewbaseaddress PBASEADDRESS !

    - This assembler comes with the standard Forth control flow shortcut words.

      - SHORTBRANCH, RESOLVE-BRANCH are supported.

      - IF, ELSE, THEN, BEGIN, WHILE, REPEAT, and UNTIL, are supported.

      - The condition codes are: 

        - EQ    // zero flag is set    ( result was 0 )
        - ZS    // zero flag is set    ( result was 0 )
        - NE    // zero flag is clear  ( result was not 0 )
        - NZ    // zero flag is clear  ( result was not 0 )
 
        - CS    // carry flag is set   
        - NC    // carry flag is clear
  
        - GEU   // unsigned
        - LTU   // unsigned   
        
        - MI    // sign flag is set    ( highest bit was set... 32 or 64 bit operations only )
        - PL    // sign flag is clear  ( highest bit was clear... 32 or 64 bit operations only )

        - VS    // overflow flag is set
        - VC    // overflow flag is clear

        - HI
        - LS

        - GTU    // unsigned
        - LEU    // unsigned

        - GE     // signed
        - LT     // signed

        - GT     // signed
        - LE     // signed

        - ALWAYS 
        - AL
        - NEVER  // ARM64 instructions treat NEVER the same as an ALWAYS. The helper control flow words compile a NOP, if needed.
        - NV     // ARM64 instructions treat NEVER the same as an ALWAYS. The helper control flow words compile a NOP, if needed.
                 // See section C1.2.4 of the Arm Architecture Reference Manual for A-profile architecture.

    - I have some convenience commands which are used to make the standard instructions. 
        Some of these words may compile multiple instructions and may trash 
          the scratch regs (SCRATCHREG1 and SCRATCHREG2). 
        I expect people will probably prefer to use the standard instructions instead of these.

        N->IR64,            ( N destIR -- )
        IR64->IR64,         ( srcIR destIR -- )
        RSP->IR64,          ( destIR -- )
        IR64->RSP,          ( srcIR -- )
        IR64+N->IR64,       ( srcIR N destIR -- )
        PC+N->PC,           ( N -- )
        PC+N->IR64,         ( N destIR -- )
        PC->IR64,           ( destIR -- )
        RSP+N->IR64,        ( N destIR -- )
        RSP+N->RSP,         ( N -- )
        [IR64]->IR64,       ( srcIR destIR -- )
        IR64->[IR64],       ( srcIR destIR -- )
        [IR64+IR64]->IR64,  ( srcIRa srcIRb destIR -- )
        [IR64+IR64]->IRSZ,  ( srcIRa srcIRb destIR size -- )
        [IR64]->IRSZ,       ( srcIR destIR size -- )
        IR64->[IR64+IR64],  ( srcIR destIRa destIRb -- )
        IRSZ->[IR64+IR64],  ( srcIR size destIRa destIRb -- )
        IRSZ->[IR64],       ( srcIR size destIR -- )
        [PC+N]->IR64,       ( n destIR -- )
        [PC+N]->IRSZ,       ( n destIR size -- )
        O->IR64,            ( ciboffset destIR -- )
        [O]->IR64,          ( ciboffset destIR -- )
        [O]->IRSZ,          ( ciboffset destIR size -- )
        [IR64+N]->IR64,     ( srcIR N destIR -- )
        [IR64+N]->IRSZ,     ( srcIR N destIR size -- )  // date of size is fetched from source
        [IR64++N]->IR64,    ( srcIR N destIR -- )
        [IR64++N]->IRSZ,    ( srcIR N destIR size -- )  // data of size is fetched from source
        IR64->[IR64++N],    ( srcIR destIR N -- )
        IRSZ->[IR64++N],    ( srcIR size destIR N -- )  // data of size is stored to dest
        [IR64]++N->IR64,    ( srcIR N destIR -- )
        [IR64]++N->IRSZ,    ( srcIR N destIR size -- )  // data of size is stored to dest 
        [RSP+N]->IR64,      ( N destreg -- )
        [RSP+N]->IRSZ,      ( N destreg size -- )       // data of size is fetched from source
        IR64->[IR64+N],     ( srcIR destIR N -- )
        IRSZ->[IR64+N],     ( srcIR size destIR N -- )  // data of size is stored to dest
        IR64->[IR64]++N,    ( srcIR destIR N -- )
        IRSZ->[IR64]++N,    ( srcIR size destIR N -- )  // data of size is stored to dest
        IR64->[RSP+N],      ( srcIR N -- )
        IRSZ->[RSP+N],      ( srcIR size N -- )         // data of size is stored to dest
        IR64IR64->IR64OP,   ( srcIRa srcIRb destIR baseopcode -- )
        IR64IR64->IR64IDPF, ( srcIRa srcIRb destIR OPID -- )
        IR64IR64->IR64IDCF, ( srcIRa srcIRb destIR OPID -- )
        IR64N->IR64IDPF,    ( srcIRa N destIR OPID -- )
        IR64N->IR64IDCF,    ( srcIRa N destIR OPID -- )
        NIR64->IR64IDPF,    ( N srcIRa destIR OPID -- )
        NIR64->IR64IDCF,    ( N srcIRa destIR OPID -- )
        IRSZ->IR64,         ( srcIR size destIR -- )

    - I also added standard instructions which I intend to port to other platforms.

        - These words may compile multiple instructions and may trash 
            the scratch regs (SCRATCHREG1 and SCRATCHREG2).

        - You can mix and match any target type specifiers. For instance, for the 2 source
            one destination instructions, all three targets can be memory. Some combinations
            that don't make sense, like both sources are N, give errors.

        - I tried to test in a way that covered all the cases, but it's possible I missed
            a combination. If someone finds something that doesnt' work, please let me know.
            Keep in mind, UPDATEFLAGS with 8 or 16 bit targets only supports changing the
            sign and zero flags correctly. Carry and overlow flags are undefined with
            8 and 16 bit UPDATEFLAGS instructions.

        - I tried to use the most effecient encodings possible for all combinations, however
            there is one ADD and SUB combination that may be done shorter, but I
            haven't put it in yet. I think ARM has an add sub int to mem instruction I can
            use to speed some things up.

        - These words pull targets off the stack.

        - A target consists of an integer and/or register followed by a target type specifier.
            For example: X3 8 [R+N]

        - An integer is just a 64 bit number such as F012345611223344

        - A register is one of X0 through X31 or R0 through R31, or RSP. Or you can just use the register's number,
            such as 0 for X0. At this time specifiying W0 through W31 does not set the size to 32 bits. Size
            is currently specified using a size modifier that follows the target type.

        - Again, the size is not determined by the register name at this time. X0 is treated the same as R0 is 
           treated the same as W0 etc...

        - specifying NOREG is not really supported yet... maybe in the next version.

        - A source target type specifier may be one of:

          none. In this case the assembler assumes the target is a register.
          N         // source is an integer
          R         // source is the value in the register
          [R]       // source is the value in memory at the address in the register
          [R+N]     // source is the value in memory at the address in the register plus an integer
          O         // source is an integer value equal to the current offset in the current compile buffer (OHERE)
                    //   setting a size for O is not supported for all cases yet...  some default to 64BITS
          [O]       // source is the value in memory at the current offset in the current compile buffer (OHERE)
          [PC+N]    // source is the value in memory at an address relative to the start of current instruction being 
                         compiled.
          [RSP+N]   // source is the value in memory at an address in register RSP plus an integer
          [R++N]    // preincrement, does R+N->R; [R+N]->    // Anyone have a better name for this?
          [R]++N    // postincrement, does [R]-> ; R+N->R;   // Anyone have a better name for this?

        - A destination target specifier may be one of:

          none. In this case the assembler assumes the target is a register.
          R         // destination is a register
          [R]       // destination is the value in memory at the address in the register
          [R+N]     // destination is the value in memory at the address in the register plus an integer
          [O]       // destination is the value in memory at the current offset in the current compile buffer (OHERE)
          [PC+N]    // destination is the value in memory at an address relative to the start of current instruction being 
                         compiled.
          [RSP+N]   // destination is the value in memory at an address in register RSP plus an integer
          [R++N]    // preincrement, does R+N->R; ->[R+N]    // Anyone have a better name for this?
          [R]++N    // postincrement, does ->[R] ; R+N->R;   // Anyone have a better name for this?

        - a target may have one or more of these modifiers immediately after it:
          
          none. In this case the default modifiers are 64BIT PRESERVEFLAGS
            if this format gets ported to other platforms, PRESERVEFLAGS may not be the default.
            I intend to have the default use the most efficient instructions. On Arm64 this is PRESERVEFLAGS.
          PF PRESERVEFLAGS UF UPDATEFLAGS 
          8BIT 16BIT 32BIT 64BIT U8BIT U16BIT U32BIT U64BIT
          N8BIT N16BIT N32BIT

        - two source targets one destination target integer operations:

          ADC,
          SBC,
          SDIV,
          ASR,
          LSR,
          SMULH,
          UDIV,
          LSL,
          ROR,
          UMULH,
          ADD,
          AND,
          BIC,
          EON,
          XNOR,
          EOR,
          ORN,
          ORR,
          OR,
          SUB,
          NAND,
          NOR,

        - one source target one destination target integer operations:

          NEG,
          NOT,
          INC,
          DEC,
          MOV,

        - two source targets integer operations:
            These operations are UPDATEFLAGS only and you do not need specify UPDATEFLAGS

          TST,
          CMP,

        - no source or destination operations:

          RET,
          NOP,

    - Convenience words to set up the Arm64 call subs frame.
        These words use the ARM store and load two registers at once instructions which aren't 
          available through the standard convenience words above.

        ENTER-FRAME, // a frame is required if you are calling subroutines so you don't trash the link register
        EXIT-FRAME,  // required if you used EXIT-FRAME to restore the link register and the frame register


    - Convenience words to help make the symbol lists for the macho doto file maker.
        
        NEW-FLAT-OSYMBOL-BUF  // makes a code buffer, import symbol list, and export symbol list
                              // Note: this saves the old current compile buffer on the DiaperGlu rstack
                              //   which is not portable to most other Forths
 
        FREE-FLAT-OSYMBOL-BUF // frees the code buffer, import symbol list, export symbol list,
                              //   and restores the old current compile buffer from the rstack

        EXPORT                // assumes you used NEW-FLAT-OSYMBOL-BUF. This adds a symbol to the export
                              //   symbol list with value = OHERE and name = next word in the current input buffer

        IMPORT                // assumes you used NEW-FLAT-OSYMBOL-BUF. This adds a symbol to the import
                              //   symbol list with value = OHERE and name = next word in the current input buffer


    - Arm64 hardware only supports setting the carry and overflow flags for 32 bit and 64 bit instructions
        so it would take a extra instructions to calculate the flags correctly if you are doing 8 or 16 bit
        operations. So to keep things simple, the carry and overflow flags are not supported if you specify
        8 or 16 bit operations. The zero and sign flags should still work if you are using 8 or 16 bit
        operations because when you sign extend a number to 64 bits, 0 is still 0, and the sign bit gets
        extended to the 63rd bit.

    - Not everything is tested. The instructions that are tested are marked in the source file. Also, I
       mostly only tested the 64 bit versions of instructions. Again, I found lots of bugs when I was
       doing my second pass through during testing. There are probably bugs in the stuff that wasn't tested.
       And I may have missed something in the stuff that was tested.

        
  2) DGMachoDototoMaker.dglu

    - This script has a word that takes a buffer filled with Arm64 object code, and an export 
      symbol list and builds a Macho compatible .o file.

    - This script also has a word that takes a buffer filled with Arm64 object code, 
        an export symbol list, and an import symbol list and builds a Macho compatible .o file.
        This means you can use the DGMachoDotoMaker with object code generated from just about
        anything. All you have to do is build the import and export symbol lists.

    - This script uses a lot of DiaperGlu specific things, including using hierarchical lists
      to hold the import and export symbol lists. This will make it difficult to port to 
      other Forths.

    - the dototestfiles and samplescripts folders show examples of using this script. 


  3) testDGArm64CrossAsm.dglu

    - this tests some of the words in the cross assembler


  4) asmtestfiles

    - this folder tests the assembler

    - to use the test:

      - put a copy of diaperglu in the parent directory of /asmtestfiles.

      - cd into asmtestfiles

      - sudo make


  5) dototestfiles

    - this folder tests the doto file maker

    - to use the test:

    - put a copy of diaperglu in the parent directory of /asmtestfiles.

      - cd into dototestfiles

      - sudo make 

      -  run testexpas testexpdglu testimpexpas testimpexpdglu to see the results.
        testexpas should give the same results as testexpdglu
        testimpexpas should give the same results as testimpexpdglu

       
  6) samplescripts

    - this folder contains some sample scripts

    - to use the samples scripts:

    - put a copy of diaperglu in the parent directory of /asmtestfiles.

      - cd into samplescripts

      - sudo make
     
                 
