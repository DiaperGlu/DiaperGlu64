04/112022 Jim Norris

There is a new way to to compile imports. See the /testosymbolbuf example for details.

12/29/2019 Jim Norris

This sample script compiles two shared libraries.
The first shared library exports the function dg_bswap.
The second shared library imports the dg_bswap function from
  the first shared library by making a .o file and using ld build the .dylib.
  ld generates the import table for you and the .dylib does all the dynamic linking
  automatically. 




To build the shared libraries and run the test:

change the directory to this subdirectory

then do  
  sudo make 

or do  
  ../../diaperglu asmimportusingld.dglu



If you want to build your own shared libraries and test them, you may run into this issue:

I was going to import the dg_bswap function libdiaperglu.dylib but...
 newer versions of Mac OS X have some security protections enabled by default including
  one that prevents people from changing the shared library search path. If you have
  those security protections enabled on your system you must:
    either copy your export shared library to the same subdirectory from where 
    you import it,
    or copy your export shared library to somewhere along the standard library search path



