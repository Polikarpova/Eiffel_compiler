echo off

set PROG="..\Win32\Debug\Ecompiler.exe" 

echo %PROG%

echo =======================
echo positive tests
echo =======================

%PROG% "../../samples/chain"
%PROG% "../../samples/nest"
%PROG% "../../samples/array_test"
%PROG% "../../samples/single_parent"
%PROG% "../../samples/inheritance"
%PROG% "../../samples/syntax/class_empty"

echo =======================
echo negative tests
echo =======================

%PROG% "../../samples/sample"
%PROG% "../../samples/syntax/class_empty_err_END"
%PROG% "../../samples/syntax/class_empty_err_name"
%PROG% "../../samples/nest_error"

pause