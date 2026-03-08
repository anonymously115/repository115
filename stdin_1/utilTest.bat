echo off
gcc -Wall -Wextra -Werror -std=c99 utilTest.c util.c -o utilTest 1>utilTest.txt 2>&1
if exist utilTest.exe (
	.\utilTest
	echo %ERRORLEVEL%
	del utilTest.exe
	del utilTest.txt
) else (
	type utilTest.txt
)
pause