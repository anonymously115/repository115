echo off
gcc -Wall -Wextra -Werror -std=c99 inputTest.c input.c util.c -o inputTest 1>inputTest.txt 2>&1
if exist inputTest.exe (
	.\inputTest
	echo %ERRORLEVEL%
	del inputTest.exe
	del inputTest.txt
) else (
	type inputTest.txt
)
pause