echo off
gcc -Wall -Wextra -Werror -std=c99 PubTest.c Pub.c Adult.c Customer.c -o PubTest 1>PubTest.txt 2>&1
if exist PubTest.exe (
	.\PubTest
	echo %ERRORLEVEL%
	del PubTest.exe
	del PubTest.txt
) else (
	type PubTest.txt
)
pause