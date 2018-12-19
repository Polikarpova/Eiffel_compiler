echo off
echo ======= Starting a java class file =======
REM add all our paths to /bin
set PATH=c:\Program Files\Java\jdk1.8.0_20\bin\;c:\Program Files\Java\jdk1.8.0_171\bin\;c:\Program Files\Java\jdk1.8.0_121\bin\;%PATH%



REM USAGE: java -classpath <c:\path/to/search;search/class/files>  <class name to start: package1.package2.class>

REM 		!! copy rtl classes to out/ first !!

java -classpath out  eiffel.HELLO_WORLD
REM java -classpath java  eiffel.HELLO_WORLD

REM так тоже работает:
REM java -classpath c:\Dev\Eiffel\repo\Eiffel_compiler\Ecompiler\Ecompiler\java\;java  eiffel.HELLO_WORLD

rem pause

REM exit