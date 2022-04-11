
objects = osymbolexport.obj \
          osymbolimport.obj

  
all: osymbolexport.lib osymbolimport.dll clean test


osymbolexport.lib : $(objects) FORCE
	LINK osymbolexport.obj /DLL /NOENTRY

osymbolimport.dll : $(objects) osymbolexport.lib FORCE
	LINK osymbolimport.obj osymbolexport.lib /DLL /NOENTRY

osymbolexport.obj : makeosymbolexportbufdoto.dglu FORCE
	..\..\diaperglu makeosymbolexportbufdoto.dglu

osymbolimport.obj : makeosymbolimportbufdoto.dglu FORCE
	..\..\diaperglu makeosymbolimportbufdoto.dglu

.PHONY: FORCE
FORCE:

.PHONY : clean
clean :
	del $(objects) *.lib *.exp

.PHONY : superclean
superclean :
	del $(objects) *.lib *.exp *.dll

.PHONY : test
test :
	..\..\diaperglu testosymboldylibs.dglu
	


