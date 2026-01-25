all : testexpas.o testimpexpas.o testexpdglu.o testimpexpdglu.o testexpas testimpexpas testexpdglu testimpexpdglu

testexpas.o : ./testexp.s FORCE
	as -target arm64-apple-macos ./testexp.s -o testexpas.o

testexpdglu.o : ./Maketestexpdgludoto.dglu FORCE
	../diaperglu Maketestexpdgludoto.dglu

testimpexpas.o : ./testimpexp.s FORCE
	as -target arm64-apple-macos ./testimpexp.s -o testimpexpas.o

testimpexpdglu.o : ./Maketestimpexpdgludoto.dglu FORCE
	../diaperglu Maketestimpexpdgludoto.dglu

testexpas : testexpas.o testexp.cpp FORCE
	cc -o testexpas testexp.cpp testexpas.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

testexpdglu : testexpdglu.o testexp.cpp FORCE
	cc -o testexpdglu testexp.cpp testexpdglu.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

testimpexpas : testimpexpas.o testimpexp.cpp FORCE
	cc -o testimpexpas testimpexp.cpp testimpexpas.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

testimpexpdglu : testimpexpdglu.o testimpexp.cpp FORCE
	cc -o testimpexpdglu testimpexp.cpp testimpexpdglu.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

clean :
	rm *.o

releaseclean :
	rm *.o testexpas testexpdglu testimpexpas testimpexpdglu

.PHONY: FORCE
FORCE:
