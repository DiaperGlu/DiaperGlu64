osapiobjects = cpux86win64msvcasm.obj \
               osapiwin64.obj 

objects = cbuffer.obj \
          cerror.obj \
          cglu.obj \
          chierarchicallist.obj \
          cinitwordlist.obj \
          clstring.obj \
          cmiscellaneous.obj \
          cwordlist.obj \
          dglumain.obj \
          forthbuffer.obj \
          forthcompiletype.obj \
          forthcore.obj \
          forthdoublenumber.obj \
          fortherror.obj \
          forthfloatingpoint.obj \
          forthglu.obj \
          forthhierarchicallist.obj \
          forthlocals.obj \
          forthlocalslstring.obj \
          forthlstringstack.obj \
          forthmiscellaneous.obj \
          forthnames.obj \
          forthprogrammingtools.obj \
          forthsearchorder.obj \
          forthstring.obj \
          forthstringstack.obj \
          forthwordlist.obj \
          compilecpux86.obj \
          win64specific.obj

testobjects = testcbuffer.obj \
              testcerror.obj \
              testcglu.obj \
              testchierarchicallist.obj \
              testclstring.obj \
              testcmiscellaneous.obj \
              testcompilecpux86.obj \
              testcwordlist.obj \
              testdglu.obj \
              testdglumain.obj \
              testforthbuffer.obj \
              testforthcore.obj \
              testforthdoublenumber.obj \
              testforthfloatingpoint.obj \
              testforthhierarchicallist.obj \
              testforthlocals.obj \
              testforthlstring.obj \
              testforthsearchorder.obj \
              testforthstring.obj \
              testwin64specific.obj

     
all: diapergluosapi diaperglu
diapergluosapi : diapergluosapi.dll diapergluosapi.lib testosapi.exe 
diaperglu : libdiaperglu.dll libdiaperglu.lib diaperglulinked.exe diaperglu.exe testdiaperglulinked.exe clean

diapergluosapi.dll : $(osapiobjects)
	LINK /DLL $(osapiobjects) user32.lib /OUT:diapergluosapi.dll

diapergluosapi.lib : $(osapiobjects)
	LIB $(osapiobjects) /DEF /OUT:diapergluosapi.lib 

libdiaperglu.dll : $(objects) $(osapiobjects)
	LINK /DLL $(objects) $(osapiobjects) user32.lib /OUT:libdiaperglu.dll

libdiaperglu.lib : $(objects) $(osapiobjects)
	LIB $(objects) $(osapiobjects) /DEF /OUT:libdiaperglu.lib 

testosapi.exe : testosapi.obj diapergluosapi.lib
	LINK testosapi.obj diapergluosapi.lib /OUT:testosapi.exe

testosapi.obj : ../testosapi.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testosapi.cpp

diaperglulinked.exe : dgluconsolelinked.obj libdiaperglu.lib ../diapergluforth.h
	LINK dgluconsolelinked.obj libdiaperglu.lib /OUT:diaperglulinked.exe

diaperglu.exe : $(objects) $(osapiobjects) dgluconsole.obj
	LINK dgluconsole.obj $(objects) $(osapiobjects) user32.lib /OUT:diaperglu.exe

testdiaperglulinked.exe : $(testobjects) libdiaperglu.lib ../testdglu.h ../diapergluforth.h
	LINK $(testobjects) libdiaperglu.lib /OUT:testdiaperglulinked.exe

osapiwin64.obj : ./osapiwin64.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ./osapiwin64.cpp

cbuffer.obj : ../cbuffer.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../cbuffer.cpp

cerror.obj : ../cerror.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../cerror.cpp

cglu.obj : ../cglu.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../cglu.cpp

chierarchicallist.obj : ../chierarchicallist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../chierarchicallist.cpp

cinitwordlist.obj : ../cinitwordlist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../cinitwordlist.cpp

clstring.obj : ../clstring.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../clstring.cpp

cmiscellaneous.obj : ../cmiscellaneous.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../cmiscellaneous.cpp

cwordlist.obj : ../cwordlist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../cwordlist.cpp

dgluconsole.obj : ../dgluconsole.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../dgluconsole.cpp

dgluconsolelinked.obj : ../dgluconsolelinked.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../dgluconsolelinked.cpp

dglumain.obj : ../dglumain.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../dglumain.cpp

forthbuffer.obj : ../forthbuffer.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthbuffer.cpp

forthcompiletype.obj : ../forthcompiletype.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthcompiletype.cpp

forthcore.obj : ../forthcore.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthcore.cpp

forthdoublenumber.obj : ../forthdoublenumber.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthdoublenumber.cpp

fortherror.obj : ../fortherror.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../fortherror.cpp

forthfloatingpoint.obj : ../forthfloatingpoint.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthfloatingpoint.cpp

forthglu.obj : ../forthglu.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthglu.cpp

forthhierarchicallist.obj : ../forthhierarchicallist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthhierarchicallist.cpp

forthlocals.obj : ../forthlocals.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthlocals.cpp

forthlocalslstring.obj : ../forthlocalslstring.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthlocalslstring.cpp

forthlstringstack.obj : ../forthlstringstack.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthlstringstack.cpp

forthmiscellaneous.obj : ../forthmiscellaneous.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthmiscellaneous.cpp

forthnames.obj : ../forthnames.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthnames.cpp

forthprogrammingtools.obj : ../forthprogrammingtools.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthprogrammingtools.cpp

forthsearchorder.obj : ../forthsearchorder.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthsearchorder.cpp

forthstring.obj : ../forthstring.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthstring.cpp

forthstringstack.obj : ../forthstringstack.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthstringstack.cpp

forthwordlist.obj : ../forthwordlist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ../forthwordlist.cpp

compilecpux86.obj : ./compilecpux86.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ./compilecpux86.cpp

win64specific.obj : ./win64specific.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_EXPORTS ./win64specific.cpp

cpux86win64msvcasm.obj : cpux86win64msvcasm.asm 
	ml64 /c cpux86win64msvcasm.asm

testcbuffer.obj : ../testcbuffer.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testcbuffer.cpp

testcerror.obj : ../testcerror.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testcerror.cpp

testcglu.obj : ../testcglu.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testcglu.cpp

testchierarchicallist.obj : ../testchierarchicallist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testchierarchicallist.cpp

testclstring.obj : ../testclstring.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testclstring.cpp

testcmiscellaneous.obj : ../testcmiscellaneous.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testcmiscellaneous.cpp

testcompilecpux86.obj : ../testcompilecpux86.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testcompilecpux86.cpp

testcwordlist.obj : ../testcwordlist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testcwordlist.cpp

testdglu.obj : ../testdglu.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testdglu.cpp

testdglumain.obj : ../testdglumain.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testdglumain.cpp

testforthbuffer.obj : ../testforthbuffer.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthbuffer.cpp

testforthcore.obj : ../testforthcore.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthcore.cpp

testforthdoublenumber.obj : ../testforthdoublenumber.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthdoublenumber.cpp

testforthfloatingpoint.obj : ../testforthfloatingpoint.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthfloatingpoint.cpp

testforthhierarchicallist.obj : ../testforthhierarchicallist.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthhierarchicallist.cpp

testforthlocals.obj : ../testforthlocals.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthlocals.cpp

testforthlstring.obj : ../testforthlstring.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthlstring.cpp

testforthsearchorder.obj : ../testforthsearchorder.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthsearchorder.cpp

testforthstring.obj : ../testforthstring.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ../testforthstring.cpp

testwin64specific.obj: ./testwin64specific.cpp ../diapergluforth.h
	cl /c /Fo /DDGLU_OS_WIN64 /DDGLU_IMPORTS ./testwin64specific.cpp

.PHONY : clean
clean : cleantestosapi
	del $(objects) $(testobjects) libdiaperglu.exp diaperglu.exp diaperglu.lib dgluconsole.obj dgluconsolelinked.obj

.PHONY : cleantestosapi
cleantestosapi :
	del $(testosapiobjects) $(osapiobjects) diapergluosapi.exp testosapi.obj testdglumain.obj 

.PHONY : superclean
superclean :
	del libdiaperglu.dll libdiaperglu.lib diaperglu.exe diapergluosapi.dll diapergluosapi.lib testdiaperglulinked.exe testosapi.exe diaperglulinked.exe testdiaperglulinked.exp testdiaperglulinked.lib

.PHONY : releaseclean
releaseclean :
	del libdiaperglu.dll libdiaperglu.lib diapergluosapi.dll diapergluosapi.lib testdiaperglulinked.exe testosapi.exe diaperglulinked.exe 

