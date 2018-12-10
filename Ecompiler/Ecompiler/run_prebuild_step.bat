echo off
echo  Compliling /java/*/* sources ...
REM add all our paths to /bin
set PATH=c:\Program Files\Java\jdk1.8.0_20\bin\;c:\Program Files\Java\jdk1.8.0_171\bin\;c:\Program Files\Java\jdk1.8.0_121\bin\;%PATH%

REM javac -sourcepath <path>         Specify where to find input source files

javac java/eiffel/*.java   java/rtl/*.java 
REM javac -sourcepath java/eiffel/*.java
REM javac  java/*.java
 REM -verbose > java/jc_output.txt
REM javac -help
REM javac -version
REM javac -sourcepath java/

rem pause

REM exit