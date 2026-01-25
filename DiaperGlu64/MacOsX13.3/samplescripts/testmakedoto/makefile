# 24 Jan 2026 Jim Norris - replaced -mmacosx-version-min=12.0 with -target x86_64-apple-macos11.0
# 24 Jan 2026 Jim Norris - removed -no_uuid -no_eh_labels as uuid and eh_labels are now required

all: libtestmakedoto.dylib testmakedotolinked test clean


libtestmakedoto.dylib : testmakedoto.o
	ld -demangle -dynamic -dylib -arch x86_64 -platform_version macos 12.0.0 12.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o libtestmakedoto.dylib -L. -L/usr/local/lib testmakedoto.o -lSystem

testmakedoto.o : testmakedoto.dglu
	../../diaperglu testmakedoto.dglu

testmakedotolinked : testmakedoto.o
	cc testmakedotomain.cpp -o testmakedotolinked -mstackrealign -target x86_64-apple-macos11.0 -L. -L../.. -ltestmakedoto -DDGLU_OS_FREEBSD


.PHONY : test
test :
	./testmakedotolinked

.PHONY : clean
clean :
	rm testmakedoto.o
	
.PHONY : superclean
superclean :
	rm libtestmakedoto.dylib testmakedotolinked

