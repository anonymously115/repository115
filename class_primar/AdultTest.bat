gcc -Wall -Wextra -Werror -std=c99 AdultTest.c Adult.c Customer.c -o AdultTest 1>AdultTest.txt 2>&1
.\AdultTest
echo %ERRORLEVEL%
del AdultTest.exe
pause