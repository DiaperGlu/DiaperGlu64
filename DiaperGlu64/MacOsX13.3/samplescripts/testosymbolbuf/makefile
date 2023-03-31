
all: libosymbolexport.dylib libosymbolimport.dylib test clean


libosymbolexport.dylib : osymbolexport.o
	ld -demangle -dynamic -dylib -no_uuid -no_eh_labels -arch x86_64 -platform_version macos 12.0.0 12.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o libosymbolexport.dylib -L. -L/usr/local/lib osymbolexport.o -lSystem

libosymbolimport.dylib : osymbolimport.o
	ld -demangle -dynamic -dylib -no_uuid -no_eh_labels -arch x86_64 -platform_version macos 12.0.0 12.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o libosymbolimport.dylib -L. -L/usr/local/lib osymbolimport.o -losymbolexport -lSystem

osymbolexport.o : makeosymbolexportbufdoto.dglu
	../../diaperglu makeosymbolexportbufdoto.dglu

osymbolimport.o : makeosymbolimportbufdoto.dglu
	../../diaperglu makeosymbolimportbufdoto.dglu

.PHONY : clean
clean :
	rm osymbolexport.o osymbolimport.o

.PHONY : test
test :
	../../diaperglu testosymboldylibs.dglu
	
.PHONY : superclean
superclean :
	rm libosymbolexport.dylib libosymbolimport.dylib 

