AR Disassembly Project 

  This version of the Alternate Reality Disassembly Project was tested using: 
    
    DiaperGlu v5.15                         https://github.com/DiaperGlu/DiaperGlu64
    MySQL v9.2.0 for Win64                  https://dev.mysql.com/downloads/mysql/
    MySQL ODBC Connector v9.2.0 for Win64   https://dev.mysql.com/downloads/connector/odbc/
    ARDisassembly v2.0                      https://github.com/DiaperGlu/DiaperGlu64
    ardbbackup2025May03.pkl64               included in the ARDisassembly v2.0 folder
  
  Alternate Reality disk images and data used with permission of the copyright holder Philip Price.

    https://forums.atariage.com/topic/159323-alternate-reality-advanced-music-processor-disassembly/#comment-2806016
    https://forums.atariage.com/profile/8123-philip-price/
    Please note that this permission is for non-commercial uses only.


  CityGameOSWithCombat has the combined game operating system files with the combat swap files loaded. 
    Hopefully all of it is decoded. Phil kept some things encrypted in memory except just when they are used. 


  Installation:

    Install IIS if needed: Start -> Windows System -> Control Panel -> Programs -> Turn Windows features on or off
      Make sure Internet Information Services is checked with
      sub catagories Web Management Tools and World Wide Web Services are checked
      Make sure it is running. I think this is in Start -> Windows Administrative Tools -> IIS (look at right side)

    Install MySQL Community Edition if needed.

    Configure MySQL Community Edition if needed.<br>
      Start -> MySQL -> MySQL Configurator
      Config type is Development Computer
      Connectivity is TCP/IP on Port: 3306 and X Protocol Port: 33060
      with Open Windows Firewall ports for network access checked
      click Next
      set password$ in config.dgluinc to the MySQL root password (default is myrootpassword)
      click Next
      Configure MySQL Server as a Windows Service is checked.
      Windows Service Name is MySQL92
      Start the MySQL Server at System Startup is checked.
      Run Windows Service as a Standard System Account is selected.
      Sample databases are not needed.

    Install MySQL Community Edition ODBC Connector if needed.

    Add a 64 bit ODBC connection:<br>
      Start->Windows Administrative Tools->ODBC Data Source Administrator (64bit)
      Add button -> Select MySQL ODBC 9.2 ANSI Driver -> Finish button
      Enter a Data Source Name. This much match the sqlserver$ in config.dgluinc (default is ARDBMYSQLANSI9.2)
      Description does not matter.
      Use TCP/IP Server: with Port: 3306. This is the default. The middle field is left blank.
      You do not need to choose a username, password, or database. The test button will not work if you don't.
      You could put in a username, password, and database, but the database does not exist yet.

    Install Visual Studio command line tools if needed:
      https://visualstudio.microsoft.com/downloads/
      (Tested with 2019 tools)

    Download and build DiaperGlu.<br>
      Instructions are in DiaperGlu64/docs/building.htm. I've been told this takes around 10 minutes the first time.

    Copy the /ardisassembly folder and it's contents from https://github.com/DiaperGlu/DiaperGlu64 to C:/inetpub/wwwroot/cgi-bin/

    Edit config.dgluinc and set sqlserver$ sqlusername$ and sqlpassword$ if you haven't already done so.
      You may also want to write down or remember the various passwords in config.dgluinc.
      And, yes, the space after each $" is required. It's a Forth thing.

    Set up diaperglu as a CGI script engine:
      Make a directory under C:/inetpub/wwwroot/cgi-bin/ called /myphysicaldirectory
      Copy diaperglu.exe to C:/inetpub/wwwroot/cgi-bin/myphysicaldirectory
      In the IIS Mananager, on the site tree on the left, click on myphysicaldirectory to highlight it
      Double click Handler Mappings
      On the right, click Add Script Map
      Request path is *.dglu
      Executable is C:\inetpub\wwwroot\myphysicaldirectory\diaperglu.exe
      Name is dotdglucgi3
      Under Request Restrictions, only file and script are selected (default I believe)
      Click OK
      For security reasons you may want to restrict the .dglu mapping to just the ardisassembly folder 
        if it's possible... but I have not tested this.

     Open your browser and browse to http://localhost/cgi-bin/ardisassembly/index.dglu.
       You should see the home page.

     Click on the admin tab on the left.
       Under Load a 64 bit packed database ...:
       use backup filename ardbbackup2025May03.pkl64
       use admin password from config.dgluinc (default is whensomearelost)
       click Submit for Load a 64 bit packed database ...
       Please be patient, it takes awhile.
 

