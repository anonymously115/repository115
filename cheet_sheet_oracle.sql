-- SHOW DATABASES;
SELECT username FROM all_users;

-- SHOW TABLES;
SELECT table_name FROM user_tables;

-- SHOW COLUMNS FROM t;
DESC t;
SELECT * FROM all_tab_columns WHERE owner = 'OWNER' AND table_name = 'TABLE_NAME' ORDER BY column_id;;

-- SHOW CREATE TABLE emp;
DBMS_METADATA.GET_DDL('TABLE', 'EMP');

-- SHOW INDEX FROM t;
SELECT * FROM user_indexes;
SELCT * FROM user_ind_columns;
