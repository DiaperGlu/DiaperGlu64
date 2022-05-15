
  
all: libmytestlib.dylib


libmytestlib.dylib : testmakedylib.dglu FORCE
	../../diaperglu testmakedylib.dglu

testmakedylibgas.o : testmakedylibgas.s
	as -mmacosx-version-min=11.0 ./testmakedylibgas.s -o testmakedylibgas.o


.PHONY: FORCE
FORCE:
	
superclean : FORCE
	rm libmytestlib.dylib 

