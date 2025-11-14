echo off
gcc -Wall -Wextra -Werror -std=c99 memory.c Pub.c Adult.c Customer.c -o memory 1>memory.txt 2>&1
if exist memory.exe (
	.\memory
	echo %ERRORLEVEL%
	del memory.exe
	del memory.txt
) else (
	type memory.txt
)
pause