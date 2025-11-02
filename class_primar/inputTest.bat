gcc -Wall -Wextra -Werror -std=c99 inputTest.c input.c util.c -o inputTest 1>inputTest.txt 2>&1
.\inputTest
echo %ERRORLEVEL%
del inputTest.exe
pause