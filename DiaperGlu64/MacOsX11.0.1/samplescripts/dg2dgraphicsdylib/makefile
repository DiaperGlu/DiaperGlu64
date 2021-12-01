objects = dg2dgraphics.o \
          cdg2dgraphics.o

testobjects = testdg2dgraphicsmain.o

.PHONY: all
all : libdg2dgraphics.dylib.1.0 testdg2dgraphics test test2 clean

dg2dgraphics.o : makedg2dgraphicsdylib.dglu FORCE
	../../diaperglu makedg2dgraphicsdylib.dglu

cdg2dgraphics.o : ./cdg2dgraphics.cpp ./dg2dgraphics.h
	cc -c ./cdg2dgraphics.cpp -mmacosx-version-min=10.11 -mstackrealign -DDGLU_OS_FREEBSD

libdg2dgraphics.dylib.1.0 : $(objects) ./dg2dgraphics.h
	ld -demangle -dynamic -dylib -arch x86_64 -platform_version macos 11.0.0 11.1 -syslibroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -o libdg2dgraphics.dylib -L/usr/local/lib $(objects)

testdg2dgraphics : $(testobjects) ./dg2dgraphics.h libdg2dgraphics.dylib.1.0 FORCE
	cc $(testobjects) -o testdg2dgraphics -mstackrealign -mmacosx-version-min=10.11 -lc -L. -ldg2dgraphics -lstdc++ -DDGLU_OS_FREEBSD

testdg2dgraphicsmain.o : ./testdg2dgraphicsmain.cpp ./dg2dgraphics.h
	cc -c ./testdg2dgraphicsmain.cpp -mmacosx-version-min=10.11 -mstackrealign -DDGLU_OS_FREEBSD

.PHONY: test
test : 
	../../diaperglu testdg2dgraphicsdylib.dglu

.PHONY: test2
test2 : 
	./testdg2dgraphics

.PHONY: FORCE
FORCE:

.PHONY : clean
clean :
	rm $(objects) $(testobjects)

superclean : FORCE
	rm libdg2dgraphics.dylib testdg2dgraphics



	


