echo off
echo  =  
echo ======= View %~nx1% =======
echo  =  

REM add all our paths to /bin
set PATH=c:\Program Files\Java\jdk1.8.0_171\bin\;c:\Program Files\Java\jdk1.8.0_121\bin\;%PATH%
javap -c -s -verbose %1

rem pause