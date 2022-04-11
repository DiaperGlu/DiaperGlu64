
objects = osymbolexport.o \
          osymbolimport.o

  
all: libosymbolexport.dylib libosymbolimport.dylib test clean


libosymbolexport.dylib : $(objects)
	ld -macosx_version_min 10.11 -dynamic -dylib -no_uuid -no_eh_labels -o libosymbolexport.dylib $(objects)

libosymbolimport.dylib : $(objects)
	ld -macosx_version_min 10.11 -dynamic -dylib -no_uuid -no_eh_labels -o libosymbolimport.dylib $(objects) -L. -losymbolexport

osymbolexport.o : makeosymbolexportbufdoto.dglu
	../../diaperglu makeosymbolexportbufdoto.dglu

osymbolimport.o : makeosymbolimportbufdoto.dglu
	../../diaperglu makeosymbolimportbufdoto.dglu

.PHONY : clean
clean :
	rm $(objects)

.PHONY : test
test :
	../../diaperglu testosymboldylibs.dglu
	
.PHONY : superclean
superclean :
	rm libosymbolexport.dylib libosymbolimport.dylib 

