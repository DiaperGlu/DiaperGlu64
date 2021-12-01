
.PHONY: all
all : life.dglib test

life.dglib : lifedglib.dglu FORCE
	../../diaperglu lifedglib.dglu


.PHONY: test
test : 
	../../diaperglu testlifedglib.dglu

.PHONY: FORCE
FORCE:

superclean : FORCE
	rm life.dglib life.glulist


