gcc -Wall -Wextra -Werror -std=c99 test.c -o test 1>test.txt 2>&1
.\test
echo %ERRORLEVEL%
del test.exe
pause