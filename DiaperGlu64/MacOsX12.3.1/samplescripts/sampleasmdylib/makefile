
.PHONY: all
all : libsampleasmdylib.dylib testsampleasmdylib clean test

libsampleasmdylib.dylib : makesampleasmdylibusingld.dglu sampleasmdylib.dglu FORCE
	../../diaperglu makesampleasmdylibusingld.dglu

testsampleasmdylib : testsampleasmdylib.cpp FORCE
	cc testsampleasmdylib.cpp -o testsampleasmdylib -mstackrealign -mmacosx-version-min=12.0 -L. -L../.. -lsampleasmdylib

.PHONY: clean 
clean :
	rm sampleasmdylib.o

.PHONY: test
test : 
	./testsampleasmdylib

.PHONY: FORCE
FORCE:

superclean : FORCE
	rm libsampleasmdylib.dylib testsampleasmdylib



	


