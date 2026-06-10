CREATE TABLE temporary(id INTEGER PRIMARY KEY, name VARCHAR2(8));
SET SERVEROUTPUT ON;
BEGIN
    DBMS_OUTPUT.PUT_LINE('hello, world');
    FOR i IN 1..100 LOOP
        IF MOD(i, 15) = 0
            THEN INSERT INTO temporary(id, name) VALUES (i, 'FizzBuzz');
        ELSIF MOD(i, 3) = 0
            THEN INSERT INTO temporary(id, name) VALUES (i, 'Fizz');
        ELSIF MOD(i, 5) = 0
            THEN INSERT INTO temporary(id, name) VALUES (i, 'Buzz');
        ELSE INSERT INTO temporary(id, name) VALUES (i, i);
        END IF;
    END LOOP;
END;
/
SET SERVEROUTPUT OFF;
SELECT * FROM temporary;
DROP TABLE temporary;
