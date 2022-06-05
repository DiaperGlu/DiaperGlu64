
objects = osymbolimport.obj

  
all: osymbolimport.dll clean test


osymbolimport.dll : $(objects) FORCE
	LINK osymbolimport.obj User32.lib /DLL /NOENTRY

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
	


