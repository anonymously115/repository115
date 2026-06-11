CREATE TABLE temporary(id INTEGER PRIMARY KEY, name VARCHAR2(8));
BEGIN
    FOR i IN 1..100 LOOP
        IF MOD(i, 15) = 0
            THEN INSERT INTO temporary(id, name) VALUES (i, 'FizzBuzz');
        ELSIF MOD(i, 3) = 0
            THEN INSERT INTO temporary(id, name) VALUES (i, 'Fizz');
        ELSIF MOD(i, 5) = 0
            THEN INSERT INTO temporary(id, name) VALUES (i, 'Buzz');
        ELSE INSERT INTO temporary(id, name) VALUES (i, TO_CHAR(i));
        END IF;
    END LOOP;
END;
/
SELECT * FROM temporary ORDER BY id;
SET SERVEROUTPUT ON;
DECLARE
    CURSOR c IS SELECT * FROM temporary ORDER BY id;
    r c%ROWTYPE;
BEGIN
    IF NOT c%ISOPEN THEN
        OPEN c;
    END IF;
    LOOP
        FETCH c INTO r;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(r.id || ': ' || r.name);
    END LOOP;
    CLOSE c;
END;
/
SET SERVEROUTPUT OFF;
DROP TABLE temporary;
