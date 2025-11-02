gcc -Wall -Wextra -Werror -std=c99 CustomerTest.c Customer.c -o CustomerTest 1>CustomerTest.txt 2>&1
.\CustomerTest
echo %ERRORLEVEL%
del CustomerTest.exe
pause