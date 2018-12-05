echo off
echo  =  
echo ======= View %~nx1% =======
echo  =  

set PATH=c:\Program Files\Java\jdk1.8.0_171\bin\;%PATH%
javap -c -s -verbose %1

rem pause