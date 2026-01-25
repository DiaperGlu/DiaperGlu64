all : helloworld.o helloworld simplehelloworld.o simplehelloworld execute executesimple

helloworld.o : ./Makehelloworlddoto.dglu FORCE
	../diaperglu Makehelloworlddoto.dglu

helloworld : helloworld.o FORCE
	cc -o helloworld helloworld.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

simplehelloworld.o : ./Makesimplehelloworlddoto.dglu FORCE
	../diaperglu Makesimplehelloworlddoto.dglu

simplehelloworld : simplehelloworld.o FORCE
	cc -o simplehelloworld simplehelloworld.o -target arm64-apple-macos -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

execute :
	./helloworld

executesimple :
	./simplehelloworld

clean :
	rm *.o

releaseclean :
	rm *.o helloworld simplehelloworld

.PHONY: FORCE
FORCE:

