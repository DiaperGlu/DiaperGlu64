
.PHONY: all
all : lifelib.dylib test

lifelib.dylib : makelifedylib.dglu FORCE
	../../diaperglu makelifedylib.dglu


.PHONY: test
test : 
	../../diaperglu testlifedylib.dglu

.PHONY: FORCE
FORCE:

.PHONY: superclean
superclean:
	rm liblife.dylib

	


