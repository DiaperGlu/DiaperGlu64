
.PHONY: all
all : helloworld64 clean

helloworld64.o : makehelloworld64doto.dglu FORCE
	../../diaperglu makehelloworld64doto.dglu

helloworld64 : helloworld64.o FORCE 
	ld -e _myhelloworldstart -no_uuid -no_eh_labels -demangle -dynamic -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o helloworld64 -L/usr/local/lib helloworld64.o -lSystem

.PHONY: clean 
clean :
	rm helloworld64.o

.PHONY: FORCE
FORCE:

superclean : FORCE
	rm helloworld64

# ld -execute -macosx_version_min 10.11 -no_uuid -no_eh_labels -lSystem -e _myhelloworldstart -o helloworld64 helloworld64.o