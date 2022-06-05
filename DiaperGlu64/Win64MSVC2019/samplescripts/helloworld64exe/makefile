all : helloworld64.exe clean test

helloworld64.obj : makehelloworld64doto.dglu
	..\..\diaperglu makehelloworld64doto.dglu

helloworld64.exe : helloworld64.obj 
	LINK helloworld64.obj kernel32.lib user32.lib /OUT:helloworld64.exe /ENTRY:myhelloworldstart /SUBSYSTEM:CONSOLE 

.PHONY : clean
clean :
	del helloworld64.obj

.PHONY : test
test :
	helloworld64.exe

.PHONY : superclean
superclean :
	del helloworld64.exe


