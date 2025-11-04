echo off
gcc -Wall -Wextra -Werror -std=c99 test.c -o test 1>test.txt 2>&1
if exist test.exe (
    .\test
    echo %ERRORLEVEL%
    del test.exe
    del test.txt
) else (
    type test.txt
)
pause