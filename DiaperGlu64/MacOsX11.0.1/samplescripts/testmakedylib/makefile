
  
all: libmytestlib.dylib


libmytestlib.dylib : testmakedylib.dglu FORCE
	../../diaperglu testmakedylib.dglu


.PHONY: FORCE
FORCE:
	
superclean : FORCE
	rm libmytestlib.dylib 

