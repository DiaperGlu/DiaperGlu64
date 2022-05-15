objects = compilecpux86.o \
          cpux86macosxgccsignalcatch.o \
          cpux86macosxgccasm.o \
          osapimacosxgcc.o \
          cbuffer.o \
          cerror.o \
          cglu.o \
          chierarchicallist.o \
          cinitwordlist.o \
          clstring.o \
          clstringqueue.o \
          cmiscellaneous.o \
          cwordlist.o \
          dglumain.o \
          forthbuffer.o \
          forthcompiletype.o \
          forthcore.o \
          forthdoublenumber.o \
          fortherror.o \
          forthfloatingpoint.o \
          forthglu.o \
          forthhierarchicallist.o \
          forthlocals.o \
          forthlocalslstring.o \
          forthlstringstack.o \
          forthmiscellaneous.o \
          forthnames.o \
          forthprogrammingtools.o \
          forthsearchorder.o \
          forthstring.o \
          forthstringstack.o \
          forthwordlist.o

testobjects = testcbuffer.o \
              testcerror.o \
              testcompilecpux86.o \
              testchierarchicallist.o \
              testclstring.o \
              testclstringqueue.o \
              testcmiscellaneous.o \
              testcwordlist.o \
              testcglu.o \
              testdglu.o \
              testdglumain.o \
              testforthbuffer.o \
              testforthcore.o \
              testforthdoublenumber.o \
              testforthfloatingpoint.o \
              testforthhierarchicallist.o \
              testforthlocals.o \
              testforthlstring.o \
              testforthsearchorder.o \
              testforthstring.o

  
all: libdiaperglu.dylib diaperglulinked diaperglu testosapi testdiaperglulinked clean

diaperglulinked : ../dgluconsolelinked.cpp ../diapergluforth.h libdiaperglu.dylib FORCE
	cc ../dgluconsolelinked.cpp -o diaperglulinked -mstackrealign -mmacosx-version-min=11.0 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lc -lstdc++ -L. -ldiaperglu -lobjc -DDGLU_OS_FREEBSD

diaperglu : $(objects) dgluconsole.o FORCE
	cc -o diaperglu dgluconsole.o $(objects) -mstackrealign -mmacosx-version-min=11.0 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lstdc++ -lc -L. -lobjc

libdiaperglu.dylib : $(objects) FORCE
	ld -demangle -dynamic -dylib -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o libdiaperglu.dylib -L/usr/local/lib $(objects) -lsystem

testosapi : ../testosapi.cpp ../diapergluforth.h libdiaperglu.dylib FORCE
	cc ../testosapi.cpp -o testosapi -mstackrealign -mmacosx-version-min=11.0 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lc -L. -ldiaperglu -lstdc++ -DDGLU_OS_FREEBSD

testdiaperglulinked : $(testobjects) FORCE
	cc $(testobjects) -o testdiaperglulinked -mstackrealign -mmacosx-version-min=11.0 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib -lc -L. -ldiaperglu -lstdc++ -DDGLU_OS_FREEBSD

compilecpux86.o : ./compilecpux86.cpp ../diapergluforth.h
	cc -c ./compilecpux86.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cpux86macosxgccasm.o : ./cpux86macosxgccasm.s ../diapergluforth.h
	as -mmacosx-version-min=11.0 ./cpux86macosxgccasm.s -o cpux86macosxgccasm.o
cpux86macosxgccsignalcatch.o : ./cpux86macosxgccsignalcatch.cpp ../diapergluforth.h
	cc -c ./cpux86macosxgccsignalcatch.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
osapimacosxgcc.o : ./osapimacosxgcc.cpp ../diapergluforth.h
	cc -c ./osapimacosxgcc.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cbuffer.o : ../cbuffer.cpp ../diapergluforth.h
	cc -c ../cbuffer.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cerror.o : ../cerror.cpp ../diapergluforth.h
	cc -c ../cerror.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cglu.o : ../cglu.cpp ../diapergluforth.h
	cc -c ../cglu.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
chierarchicallist.o : ../chierarchicallist.cpp ../diapergluforth.h
	cc -c ../chierarchicallist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cinitwordlist.o : ../cinitwordlist.cpp ../diapergluforth.h
	cc -c ../cinitwordlist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
clstring.o : ../clstring.cpp ../diapergluforth.h
	cc -c ../clstring.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
clstringqueue.o : ../clstringqueue.cpp ../diapergluforth.h
	cc -c ../clstringqueue.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cmiscellaneous.o : ../cmiscellaneous.cpp ../diapergluforth.h
	cc -c ../cmiscellaneous.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
cwordlist.o : ../cwordlist.cpp ../diapergluforth.h
	cc -c ../cwordlist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
dgluconsole.o : ../dgluconsole.cpp ../diapergluforth.h
	cc -c ../dgluconsole.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
dglumain.o : ../dglumain.cpp ../diapergluforth.h
	cc -c ../dglumain.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthbuffer.o : ../forthbuffer.cpp ../diapergluforth.h
	cc -c ../forthbuffer.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthcompiletype.o : ../forthcompiletype.cpp ../diapergluforth.h
	cc -c ../forthcompiletype.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthcore.o : ../forthcore.cpp ../diapergluforth.h
	cc -c ../forthcore.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthdoublenumber.o : ../forthdoublenumber.cpp ../diapergluforth.h
	cc -c ../forthdoublenumber.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
fortherror.o : ../fortherror.cpp ../diapergluforth.h
	cc -c ../fortherror.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthfloatingpoint.o : ../forthfloatingpoint.cpp ../diapergluforth.h
	cc -c ../forthfloatingpoint.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthglu.o : ../forthglu.cpp ../diapergluforth.h
	cc -c ../forthglu.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthlocals.o : ../forthlocals.cpp ../diapergluforth.h
	cc -c ../forthlocals.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthlocalslstring.o : ../forthlocalslstring.cpp ../diapergluforth.h
	cc -c ../forthlocalslstring.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthhierarchicallist.o : ../forthhierarchicallist.cpp ../diapergluforth.h
	cc -c ../forthhierarchicallist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthlstringstack.o : ../forthlstringstack.cpp ../diapergluforth.h
	cc -c ../forthlstringstack.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthmiscellaneous.o : ../forthmiscellaneous.cpp ../diapergluforth.h
	cc -c ../forthmiscellaneous.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthnames.o : ../forthnames.cpp ../diapergluforth.h
	cc -c ../forthnames.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthprogrammingtools.o : ../forthprogrammingtools.cpp ../diapergluforth.h
	cc -c ../forthprogrammingtools.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthsearchorder.o : ../forthsearchorder.cpp ../diapergluforth.h
	cc -c ../forthsearchorder.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthstring.o : ../forthstring.cpp ../diapergluforth.h
	cc -c ../forthstring.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthstringstack.o : ../forthstringstack.cpp ../diapergluforth.h
	cc -c ../forthstringstack.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
forthwordlist.o : ../forthwordlist.cpp ../diapergluforth.h
	cc -c ../forthwordlist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testcbuffer.o : ../testcbuffer.cpp ../diapergluforth.h
	cc -c ../testcbuffer.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testcerror.o : ../testcerror.cpp ../diapergluforth.h
	cc -c ../testcerror.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testcglu.o : ../testcglu.cpp ../diapergluforth.h
	cc -c ../testcglu.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testchierarchicallist.o : ../testchierarchicallist.cpp ../diapergluforth.h
	cc -c ../testchierarchicallist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testclstring.o : ../testclstring.cpp ../diapergluforth.h
	cc -c ../testclstring.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testclstringqueue.o : ../testclstringqueue.cpp ../diapergluforth.h
	cc -c ../testclstringqueue.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testcmiscellaneous.o : ../testcmiscellaneous.cpp ../diapergluforth.h
	cc -c ../testcmiscellaneous.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testcompilecpux86.o : ../testcompilecpux86.cpp ../diapergluforth.h
	cc -c ../testcompilecpux86.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testcwordlist.o : ../testcwordlist.cpp ../diapergluforth.h
	cc -c ../testcwordlist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testdglu.o : ../testdglu.cpp ../diapergluforth.h
	cc -c ../testdglu.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testdglumain.o : ../testdglumain.cpp ../diapergluforth.h
	cc -c ../testdglumain.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthbuffer.o : ../testforthbuffer.cpp ../diapergluforth.h
	cc -c ../testforthbuffer.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthcore.o : ../testforthcore.cpp ../diapergluforth.h
	cc -c ../testforthcore.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthdoublenumber.o : ../testforthdoublenumber.cpp ../diapergluforth.h
	cc -c ../testforthdoublenumber.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthfloatingpoint.o : ../testforthfloatingpoint.cpp ../diapergluforth.h
	cc -c ../testforthfloatingpoint.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthhierarchicallist.o : ../testforthhierarchicallist.cpp ../diapergluforth.h
	cc -c ../testforthhierarchicallist.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthlocals.o : ../testforthlocals.cpp ../diapergluforth.h
	cc -c ../testforthlocals.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthlstring.o : ../testforthlstring.cpp ../diapergluforth.h
	cc -c ../testforthlstring.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthsearchorder.o : ../testforthsearchorder.cpp ../diapergluforth.h
	cc -c ../testforthsearchorder.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD
testforthstring.o : ../testforthstring.cpp ../diapergluforth.h
	cc -c ../testforthstring.cpp -mmacosx-version-min=11.0 -mstackrealign -DDGLU_OS_FREEBSD

.PHONY : FORCE
FORCE:

.PHONY : clean
clean :
	rm $(objects) $(testobjects) dgluconsole.o

superclean : FORCE
	rm diaperglu diaperglulinked libdiaperglu.dylib libnodiaperglu.dylib nodiaperglu nodiaperglulinked testdiaperglulinked testosapi testnodiaperglulinked testnodiaperosapi

releaseclean : FORCE
	rm diaperglulinked libdiaperglu.dylib nodiaperglulinked libnodiaperglu.dylib testosapi testnodiaperosapi testdiaperglulinked testnodiaperglulinked .* samplescripts/.* ../.* ../docs/.* ../docs/dpans6v3_3/.* 

