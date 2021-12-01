
objects = testmakedoto.o

  
all: libtestmakedoto.dylib testmakedotolinked test clean


libtestmakedoto.dylib : $(objects)
	ld -macosx_version_min 10.11 -dynamic -dylib -no_uuid -no_eh_labels -o libtestmakedoto.dylib $(objects)

testmakedoto.o : testmakedoto.dglu
	../../diaperglu testmakedoto.dglu

testmakedotolinked : testmakedoto.o
	cc testmakedotomain.cpp -o testmakedotolinked -mstackrealign -mmacosx-version-min=10.11 -L. -L../.. -ltestmakedoto -DDGLU_OS_FREEBSD


.PHONY : test
test :
	./testmakedotolinked

.PHONY : clean
clean :
	rm $(objects)
	
.PHONY : superclean
superclean :
	rm libtestmakedoto.dylib testmakedotolinked

