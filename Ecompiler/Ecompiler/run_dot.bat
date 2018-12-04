REM echo off

REM make dir test
if NOT EXIST %2 ( 
	cd %2/..
	mkdir %~n2
	REM cd %~n2
	REM cd
	)

set DOT="C:\Program Files (x86)\Graphviz2.38\bin\dot.exe" 
if NOT EXIST %DOT% ( 
	set DOT="C:\Program Files\Graphviz2.38\bin\dot.exe" 
	)

%DOT% -Tpng %1.dot -o %2/%~nx1.png
erase %~dp1*.dot

echo picture created: %2/%~nx1.png