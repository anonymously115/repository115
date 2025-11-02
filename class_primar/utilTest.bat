gcc -Wall -Wextra -Werror -std=c99 utilTest.c util.c -o utilTest 1>utilTest.txt 2>&1
.\utilTest
echo %ERRORLEVEL%
del utilTest.exe
pause