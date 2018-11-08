echo off

"C:\Program Files (x86)\Graphviz2.38\bin\dot.exe" -Tpng %1.dot -o %2\%~nx1.png
erase %~dp1*.dot

echo picture created: %2\%~nx1.png