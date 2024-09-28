
Welcome to the DiaperGlu Cross Assembler for ESP32-S3 version 1.0.


Document key:

  ar or AR    = 32 bit integer address register
  br or BR    = 1 bit flag register
  F32R        = 32 bit floating point number
  [AR]        = value in memory using the value in AR as the address

  n or N      = 32 bit signed integer
  u or U      = 32 but unsigned integer
  u8 or U8    = unsigned 8 bit integer
  n16 or N16  = signed 16 bit integer
  u16 or U16  = unsigned 16 bit integer
  u24 or U24  = unsigned 24 bit integer
  u32 or U32  = unsigned 32 bit integer
              =  in general u U n or N followed by a number is an integer with that many bits
  O           = 0 based offset in bytes from start of the current compile buffer
  [O]         = value in the current compile buffer at 0 based offset 0  

  ->          = copy the left value to the right value
  ,           = a comma at the end of a forth script word means it compiles something to the
              current compile buffer 

  op1 op2 r s t  = 4 bit Xtensa opcode fields
  w              = 2 bit Xtensa opcode field
  Q V            = 8 bit Xtensa opcode fields combining 2 of r s t
  X Y            = 1 bit Xtensa opcode fields
  imm            = x bit immediate opcode field


This cross assembler has a few script files that run under DiaperGlu on Mac and X86 Windows.

    - DiaperGlu is available from https://github.com/DiaperGlu/DiaperGlu64

    - Due to modern OS security restrictions, you need to build DiaperGlu from source. 

    - After building DiaperGlu, the simplest thing to do is copy the stand alone executable to
      the directory holding this ReadMe.txt file.


The script files included in this project:

  1) DGXtensaCrossAsm.dglu is a Forth assembler for the Xtensa instruction set.

    - Just in case you don't know what a cross assembler is, this assembler executes
      compiling words like XTADD, to compile source code into raw Xtensa object code.

    - This assembler uses a few DiaperGlu specific words, but it should be
      relatively easy to port it to another Forth.

    - Almost all the Xtensa instructions are available but most do not work the
      same way as the Xtensa assembler. The reasons for changing how they work
      were to simplify things, make them easier to remember, and to avoid name
      conflicts with hexadecimal numbers. To be more specific:

        - Xtensa instructions are prefaced with XT and have a comma after them.
          For example NOP becomes XTNOP, and BF becomes XTBF,

        - No preprocessing of integer parameters for the Xtensa XT..., 
          instructions is done. For example, if you pass -1 to the Xtensa 
          assembler for ADDI.N the Xtensa assembler converts the -1 to 0. 
          You would pass 0 to this cross assembler for ADDI.N, if you want to 
          encode -1.

        - The parameters for the instructions are not in the same order. To
          make it easier to remember, I tried to use the Forth standard ordering.
          This means sources come before destinations, and for instructions where
          the order of the sources matter, like XTSUB, the Forth standard 
          ordering is used. So if you say AR3 AR2 AR4 XTSUB, 
          it means AR3 - AR2 -> AR4. There were a couple instructions where I
          wasn't sure what to do. But since this is Forth, it is very easy to change
          things if you would prefer something else. That's the beauty of Forth.

    - This assembler compiles to the current compile buffer.

      - I recommend allocating a separate buffer and making it the current compile
        buffer. On Diaperglu, the commands to do this are:

          HEX 1000 -1 NEWBUFFER CONSTANT mybuffername
          mybuffername PCURRENTCOMPILEBUFFER !

        or if you are going to use the .o maker script then this will do  the above in one step:

          NEW-FLAT-OSYMBOL-BUF

      - Once you have compiled the code into a buffer, you have to get it to where
        you need it to go. DiaperGlu has a command to save a buffer to a file
        if that helps. It looks like this:

          mybuffername $" myfilename" SAVEFILE$

        This project also comes with a script that can convert a buffer to an
        Xtensa compatible elf .o file. This script is documented later on in this file.

    - This assembler supports setting a non zero base address, but I did not test
      the non zero case yet, and if you are making a .o file you should leave
      the base address as 0. But if you want to change it, do this:

        HEX mynewbaseaddress PBASEADDRESS !

    - This assembler comes with the standard Forth control flow shortcut words
      but are a little different because of how the Xtensa branching instructions
      work.

      - SHORTBRANCH, LONGBRANCH, RESOLVE-BRANCH, are supported.

      - IF, ELSE, THEN, LONGIF, LONGELSE, LONGTHEN, BEGIN, WHILE, REPEAT, LONGBEGIN,
        LONGWHILE, LONGREPEAT, and UNTIL, are supported but currently 
        support different than usual condition codes and may take register arguments.

      - The condition codes are compare and branch instead of just branch on condition so you may
        need to specify a register or two for the compare. I may change the names
        in future versions for portability reasons. Other processors use flags and
        I'll need condition code names that don't conflict for some of these like GE and LE.

        - BCLR ( ars art BCLR -- ) ( ars[art] == 0 ) // can't use BC because it's a hex number 
        - BSET ( ars art BSET -- ) ( ars[art] == 1 ) 
        - EQ   ( ars art EQ -- )   ( ars == art )
        - NE   ( ars art NE -- )   ( ars <> art )
        - GE   ( ars art GE -- )   ( ars >= art )  // signed
        - LT   ( ars art LT -- )   ( ars < art )   // signed
        - GT   ( ars art GT -- )   ( ars > art )   // signed
        - LE   ( ars art LE -- )   ( ars <= art )  // signed
        - GEU  ( ars art GEU -- )  ( ars U>= art ) // unsigned
        - LTU  ( ars art LTU -- )  ( ars U< art )  // unsigned
        - GTU  ( ars art GTU -- )  ( ars U> art )  // unsigned
        - LEU  ( ars art LEU -- )  ( ars U<= art ) // unsigned
        - ALL  ( ars art ALL -- )  ( notars & art == 0 ) 
            // true if all the masked bits are set
        - NALL ( ars art NALL -- ) ( notars & art <> 0 ) 
            // true if not all the masked bits are set
        - ANY  ( ars art ANY -- )  ( ars & art <> 0 ) 
            // true if any of the masked bits are set
        - NONE ( ars art NONE -- ) ( ars & art == 0 ) 
            // true if none of the masked bits are set
        - BITF ( brs BITF -- ) ( brs == 0 ) // can't use BF because it's a hex number
        - BITT ( brs BITT -- ) ( brs == 1 )
        - EQZ ( ars EQZ -- ) ( ars == 0 )
        - NEZ ( ars NEZ -- ) ( ars <> 0 )
        - GEZ ( ars GEZ -- ) ( ars >= 0 )
        - LTZ ( ars LTZ -- ) ( ars < 0 )
        - ALWAYS ( ALWAYS -- )
        - NEVER  ( NEVER -- )

      - UNTIL, automatically compiles a long branch if needed.

    - I have a couple conveniece commands to make things easier. I plan to add 
      more later, including some that will work the same on other architectures.
      For now:

      - AR+N->AR, ( arsrc n ardest -- ) ( arsrc + n -> ardest )
        - will automatically compile the most efficient instructions

      - AR->AR,
      - AR->F32R,
      - F32R->AR,
      - F32R->F32R,
      - [AR]->AR, ( arsrc ardest -- ) 
                  ( copies the 32 bit value in memory at address arsrc to ardest ) 
      - AR->[AR], ( arsrc ardest -- )
                  ( replaces the 32 bit value in memory at address ardest with arsrc )
      - U8[AR]->AR, ( arsrc ardest -- ) 
                    ( copies the unsigned 8 bit value in memory at address arsrc to ardest )
      - N16[AR]->AR, ( arsrc ardest -- ) 
                     ( copies the signed 16 bit value in memory at address arsrc to ardest )
      - U16[AR]->AR, ( arsrc ardest -- ) 
                     ( copies the unsigned 16 bit value in memory at address arsrc to ardest ) 
      - AR->U8[AR], ( arsrc ardest -- )
                    ( replaces the 8 bit value in memory at address ardest with arsrc )
      - AR->U16[AR], ( arsrc ardest -- )
                     ( replaces the 16 bit value in memory at address ardest with arsrc )
      - [O]->AR,  ( offset ardest -- ) 
                  ( copies the 32 bit value in memory at the 0 based byte offset in the current
                    compile buffer to ardest. Only offsets lower than the current compile
                    offset are supported and must be within about an 18 bit range ) 

    - Most things are tested except instructions that don't work on the ESP32-S3, and I didn't
      try to test the multiply and accumulate instructions yet.

    - If you are compiling a .o file to make functions that you can call from C, Xtensa
      uses windowed calling on C but I don't know how much of a rotation the calls use yet.
      You will need to do use an XTENTRY, instruction on entry and XTRETW.N,  or XTRETW, on exit. 
      You are guaranteed to have registers AR2 and AR3 available. AR1 is the return stack pointer,
      and AR0 is the return address. I am not sure of the parameter passing convention yet, but
      I am pretty sure the first two parameters are passed in AR2 and AR3.

      A C compatible function to return a constant looks like this:

        AR1 0 XTENTRY, ( return stack pointer is AR1, and no locals are needed )
        37 AR2 N->AR,
        XTRETW.N,

        
  2) DGXtensaElfDotoMaker.dglu

    - This script has a word that takes a buffer filled with Xtensa object code, and an export 
      symbol list and builds an Xtensa project compatible elf .o file.

    - This script uses a lot of DiaperGlu specific things, including using a hierarchical list
      to hold the export symbol list. This will make it difficult to port to other Forths.

    - makeCrossTestDoto.dglu shows an example of using this script. 

    - To use the makeexpdotobuf word in the DGXtensaElfDotoMaker.dglu script you do this:

        NEW-FLAT-OSYMBOL-BUF       
          // - makes a new buffer to hold the code and makes it the current compile buffer
          // - remember the old current compile buffer on the rstack
          // - makes two new symbol lists and makes them the current import and export symbol lists

        // Put your code here. For example:
        OSYMBOL myfunctionname  
          // - adds a symbol for the current buffer offset to the export symbol list

          AR1 0 XTENTRY,  
            // - enter a subroutine you can call from C, return stack is AR1

          37 AR2 N->AR,   
            // - put your code here, both integer and floating point results are returned in AR2

          XTRETW.N,
            // - exit a subroutine you can call from C (C makes windowed calls).

        // After the code you make the elf .o file
        PCURRENTCOMPILEBUFFER @ GETSBUFFER EH makeexpdotobuf CONSTANT mydotobufid
          // - build the elf .o file image in a new buffer

         mydotobufid $" myfilename.o" SAVEFILE$
           // - save the elf .o file image to a file

         mydotobufid FREEBUFFER
           // - free the elf .o file image buffer. If you forget, it gets freed when DiaperGlu exits.

         FREE-FLAT-OSYMBOL-BUF
           // - free the code buffer, the symbol lists, and restore the old current compile buffer 

         // - copy the new .o file to the Xtensa project's main directory. You will need to do 
         //   this every time you recompile the .o file, but I guess you already figured that out.

         // - if you haven't done so already, add the .o file's name to the idf_component_register
         //   command in the CMakeLists.txt file in your Xtensa project's 
         //   /esp/myprojectname/main/ directory.

         // - you should now be able to rebuild your Xtensa project and call the exported functions
         //   from C. To see an example of all of this, look at makeCrossTestDoto.dglu
         //   and the files in the mainreplacement directory. To rebuild the Xtensa project, if you
         //   have already installed and initialized things, do this:

              cd into /esp/yourprojectfolder/
              . $HOME/esp/esp-idf/export.sh
              idf.py build
              idf.py flash
              idf.py monitor

              use ctl-] to get out of the monitor


  3) testDGXtensaCrossAsm.dglu

    - this tests some of the words in the cross assembler


  4) makeCrossTestDoto.dglu

    - this builds a .o file that tests the use of many of the instructions and
      helper functions in this assembler... except the multiply and accumulate ones. I didn't
      even try to do those yet so I don't even know if the ESP32-S3 supports those.

    - to use the test:

      - make a copy of the hello_world project and rename the project folder testespasm

      - replace the contents of /esp/crosstest/main with the files in mainreplacement

      - cd into esp32xtensacrossasm 

      - on x86 Mac do ./diaperglu makeCrossTestDoto.dglu
        note: I only tested this script on Mac

      - on Windows do diaperglu makeCrossTestDoto.dglu

      - copy CrossTest.o into /esp/crosstest/main/

      - cd into /esp/crosstest/

      - you only need to do this command once per open terminal
          . $HOME/esp/esp-idf/export.sh

      - then do these
          idf.py fullclean
          idf.py build
          idf.py flash
          idf.py monitor

      - to get out of the monitor do ctl-]

        
       

     
                 
