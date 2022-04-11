
objects = testmakedoto.obj

  
all: testmakedoto.dll testmakedotomain.exe testfromcpp testfromdglu clean


testmakedoto.dll : $(objects)
	LINK /DLL /NOENTRY $(objects)

testmakedoto.lib : $(objects)
	LIB $(objects) /DEF /OUT:testmakedoto.lib

testmakedoto.obj : testmakedoto.dglu
	..\..\diaperglu testmakedoto.dglu

testmakedotomain.exe : testmakedoto.lib testmakedotomain.obj
	LINK testmakedotomain.obj testmakedoto.lib

testmakedotomain.obj : testmakedotomain.cpp
	cl /c /Fo testmakedotomain.cpp

.PHONY : clean testfromcpp testfromdglu

testfromcpp : testmakedotomain.exe
	testmakedotomain.exe

testfromdglu : testmakedoto.dll testdll.dglu
	..\..\diaperglu testdll.dglu

clean :
	del $(objects) testmakedoto.exp testmakedoto.lib testmakedotomain.obj
	
superclean :
	del testmakedoto.dll testmakedotomain.exe