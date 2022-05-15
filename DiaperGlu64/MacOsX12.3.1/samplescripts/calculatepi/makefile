
.PHONY: all
all : libcalculatepi.dylib testcalculatepidylib clean test

libcalculatepi.dylib : makecalculatepi.dglu calculatepi.dglu FORCE
	../../diaperglu makecalculatepi.dglu

testcalculatepidylib : testcalculatepidylib.cpp FORCE
	cc testcalculatepidylib.cpp -o testcalculatepidylib -mstackrealign -mmacosx-version-min=10.11 -L. -L../.. -lcalculatepi

.PHONY: clean 
clean :
	rm calculatepi.o

.PHONY: test
test : 
	./testcalculatepidylib

.PHONY: FORCE
FORCE:

superclean : FORCE
	rm libcalculatepi.dylib testcalculatepidylib



	


