DiaperGlu ElevatorSimulator v1.4
May 20, 2023 J.N.

For Mac Apache and DiaperGlu64 v5.10:

  copy ElevatorCGI.dglu and ElevatorContest.dglu to /Library/WebServer/CGI-Executables/

  copy Ding.mp3 to /Library/Webserver/Documents/

  open a terminal and change to directory /Library/Webserver/CGI-Executables/
    you may need to do this: chmod +x ElevatorCGI.dglu

  if you haven't already, copy diaperglu and/or nodiaperglu to /Library/WebServer/CGI-Executables/
    note: the default ElevatorCGI.dglu assumes you are using nodiaperglu

  if you haven't set up Apache for CGI, follow the instructions in DiaperGlu64/docs/usingcgi.htm

  browse to either:
    http://localhost/cgi-bin/nodiaperglu?ElevatorCGI.dglu
    or
    http://localhost/cgi-bin/ElevatorCGI.dglu

  note: http://localhost/cgi-bin/ElevatorCGI.dglu mode requires you did chmod +x ElevatorCGI.dglu
    and requires #! nodiaperglu  or  #! diaperglu  as the first line in ElevatorCGI.dglu
    using TextEdit on ElevatorCGI.dglu may require you to redo chmod +x ElevatorCGI.dglu


To run the test script on Mac:

  copy diaperglu or nodiaperglu into the ElevatorSimulator/ folder

  open a terminal and cd into the ElevatorSimulator folder

  do ./diaperglu ElevatorContestTest.dglu

  or do ./nodiaperglu ElevatorContestTest.dglu

