all : testexp.o testexp.dylib testexp execute

testexp.o : ./Maketestexpdoto.dglu FORCE
	../diaperglu Maketestexpdoto.dglu

testexp.dylib : testexp.o FORCE
	ld -demangle -dynamic -dylib -arch arm64 -platform_version macos 15.0.0 15.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o libtestexp.dylib -L/usr/local/lib testexp.o -lsystem

testexp : testexp.o FORCE
	cc -o testexp testexp.cpp testexp.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

execute :
	./testexp

clean :
	rm *.o

releaseclean :
	rm *.o libtestexp.dylib testexp
 
.PHONY: FORCE
FORCE:


