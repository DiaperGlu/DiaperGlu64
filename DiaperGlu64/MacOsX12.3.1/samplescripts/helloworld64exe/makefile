
.PHONY: all
all : helloworld64 helloworld64gas clean

helloworld64.o : makehelloworld64doto.dglu FORCE
	../../diaperglu makehelloworld64doto.dglu

helloworld64gas.o : helloworld64gas.s
	as -mmacosx-version-min=11.0 ./helloworld64gas.s -o helloworld64gas.o

helloworld64 : helloworld64.o FORCE 
	ld -e _myhelloworldstart -no_uuid -no_eh_labels -demangle -dynamic -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o helloworld64 -L/usr/local/lib helloworld64.o -lSystem

helloworld64gas : helloworld64gas.o FORCE 
	ld -e _myhelloworldstart -no_uuid -no_eh_labels -demangle -dynamic -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o helloworld64gas -L/usr/local/lib helloworld64gas.o -lSystem

.PHONY: clean 
clean :
	rm helloworld64.o helloworld64gas.o

.PHONY: FORCE
FORCE:

.PHONY: superclean
superclean : FORCE
	rm helloworld64 helloworld64gas

# ld -execute -macosx_version_min 10.11 -no_uuid -no_eh_labels -lSystem -e _myhelloworldstart -o helloworld64 helloworld64.o