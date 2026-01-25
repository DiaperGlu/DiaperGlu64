
Put diaperglu in the parent directory of this folder.

The parent directory should also have DGMachoDotoMaker.dglu

Then do:
 sudo make

This makes 8 files: 
  testexpas.o testexpdglu.o testexpas testexpdglu
  testimpexpas.o testimpexpdglu.o testimpexpas testimpexpdglu

testexpas.o and testexpdglu.o should be identical except for the order of 
  the exported symbol string names 

The nlist entries for these exported symbols are identical except for 
  their string table offsets. 

Running testexpas and testexpdglu should produce identical results.

testimpexpas.o and testimpexpdglu.o are nearly identical except 
  testimpexpdglu.o does not have the omessage or omessage2 symbol
  and the symbol name strings are in a different order

Running testimpexpas and testimpexpdglu should produce identical results.

sudo make clean removes the .o files
sudo make releaseclean removes the .o files and the executables


The test involve linking a c file with an .o file generated using the gas assembler
  and then linking the same c file with a .o file generated using the dglu .o maker
  and comparing the results.

The .dglu generated object files use raw code. If you would like to see how to
use the DGMachoDotoMaker with other code generators, this shows how to manually
generate the import export symbol lists for a raw code file.


        
       

     
                 
