Welcome to the DiaperGlu project.


------------------------------------------------------------------------------------------------


The DiaperGlu64 folder holds DiaperGlu which is 64 bit Forth script engine for 64 bit Mac OS and
  Windows running on an x86.


DiaperGlu64 has a lot of features including:

  an interactive Forth mode

  a CGI mode for hosting DHTML web pages under Apache and IIS

  a growable buffer system with managed memory

  packed memory length string arrays
   (good for things like string stacks where random element resizing/deletion is rare)
   (bad for things like databases) 

  a string stack 

  packed memory hierarchical lists 
    (good for things like symbol lists where random element resizing/deletion is rare)
    (bad for things like databases)

  an error stack

  a full x86-64 assembler with advanced features

  a linker

  sample scripts which show how to use the assembler to make shared libraries and executables

  self test scripts which check almost everything

  html based documentation

  a run time error checking system which catches errors like:
    out of memory
    bad memory accesses
    bad array indexes
    out of bounds buffer accesses

  a reduced run time checking build that runs faster


The documentation root for DiaperGlu is in /DiaperGlu64/docs/index.htm

There is a short overview of the documentation in /DiaperGlu64/ReadMe.txt
  

------------------------------------------------------------------------------------------------


The DG68HC11CrossAsm folder contains a set of DiaperGlu64 scripts that can cross compile 
  and disassemble 68HC11 code. The assembler supports Forth style control flow. I did not
  test the DG68HC11CrossAsm on an HC11 target yet so there may be a few bugs.

See /DG68HC11CrossAsm/ReadMe.txt


------------------------------------------------------------------------------------------------


The DG6502CrossAsm folder contains a set of DiaperGlu64 scripts that can cross compile 
  and disassemble 65C02 code. The assembler supports Forth style control flow. 
  The instructions for the Atari version of the 6502 are fully tested using test scripts.

See /DG6502CrossAsm/ReadMe.txt


------------------------------------------------------------------------------------------------


The MC68HC11ForthAssembler1994 folder contains a cross assembler for the 68HC11 written
  to run under Max-Forth from New Micros, Inc. 

