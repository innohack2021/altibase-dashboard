CREATE TABLE PERFORMANCE_TEST_INFO
(
    ALTIBASE_URL        CHAR(128) DEFAULT '',
    ALTIBASE_REVISION   CHAR(30),
    LAST_UPDATE         DATE,
    PER_TEST_ID         INTEGER,
    TEST_TIMES          INTEGER,
    OS                  CHAR(50),
    HOST_NAME           CHAR(20),
    ACCOUNT             CHAR(15),
    ALTIBASE_VERSION    CHAR(30),
    JENKINS_BUILD_URL   CHAR(128),
    USER_NAME           CHAR(50),
    SOURCE_NAME         CHAR(30),
    TX_LEVEL            INTEGER,
    CLIORNOT            CHAR(1),
    COMMITCT            INTEGER
);


CREATE TABLE STANDARD_TEST_RESULT
(
    PER_TEST_ID         INTEGER,
    DATA_CATEGORY       CHAR(1),
    CONNECT_TYPE        CHAR(5),
    DATA_SCALE          VARCHAR(10),
    DATA_CONTROL        CHAR(30),
    THREAD              INTEGER,
    INTERFACE           CHAR(30),
    TEST_RESULT_1       NUMERIC(10,2) DEFAULT 0,
    TEST_RESULT_2       NUMERIC(10,2) DEFAULT 0,
    TEST_RESULT_3       NUMERIC(10,2) DEFAULT 0,
    TEST_RESULT_4       NUMERIC(10,2) DEFAULT 0,
    TEST_RESULT_5       NUMERIC(10,2) DEFAULT 0,
    TEST_RESULT_AVG     NUMERIC(10,2) DEFAULT 0,
    TEST_ITEM           CHAR(50),
    TEST_START_TIME     DATE,
    TEST_END_TIME       DATE,
    CPU_USAGE_1         NUMERIC(10,2),
    CPU_USAGE_2         NUMERIC(10,2),
    CPU_USAGE_3         NUMERIC(10,2),
    CPU_USAGE_4         NUMERIC(10,2),
    CPU_USAGE_5         NUMERIC(10,2),
    CPU_USAGE_AVG       NUMERIC(10,2),
    MEMORY_USAGE_1      NUMERIC(10,2),
    MEMORY_USAGE_2      NUMERIC(10,2),
    MEMORY_USAGE_3      NUMERIC(10,2),
    MEMORY_USAGE_4      NUMERIC(10,2),
    MEMORY_USAGE_5      NUMERIC(10,2),
    MEMORY_USAGE_AVG    NUMERIC(10,2),
    NODE_ID             CHAR(10),
    LATENCY_1           NUMERIC(13,2) DEFAULT '0',
    LATENCY_2           NUMERIC(13,2) DEFAULT '0',
    LATENCY_3           NUMERIC(13,2) DEFAULT '0',
    LATENCY_4           NUMERIC(13,2) DEFAULT '0',
    LATENCY_5           NUMERIC(13,2) DEFAULT '0',
    LATENCY_AVG         NUMERIC(13,2) DEFAULT '0',
    MIN_1               NUMERIC(13,2) DEFAULT '0',
    MIN_2               NUMERIC(13,2) DEFAULT '0',
    MIN_3               NUMERIC(13,2) DEFAULT '0',
    MIN_4               NUMERIC(13,2) DEFAULT '0',
    MIN_5               NUMERIC(13,2) DEFAULT '0',
    MIN_AVG             NUMERIC(13,2) DEFAULT '0',
    MAX_1               NUMERIC(13,2) DEFAULT '0',
    MAX_2               NUMERIC(13,2) DEFAULT '0',
    MAX_3               NUMERIC(13,2) DEFAULT '0',
    MAX_4               NUMERIC(13,2) DEFAULT '0',
    MAX_5               NUMERIC(13,2) DEFAULT '0',
    MAX_AVG             NUMERIC(13,2) DEFAULT '0',
    AVG_1               NUMERIC(13,2) DEFAULT '0',
    AVG_2               NUMERIC(13,2) DEFAULT '0',
    AVG_3               NUMERIC(13,2) DEFAULT '0',
    AVG_4               NUMERIC(13,2) DEFAULT '0',
    AVG_5               NUMERIC(13,2) DEFAULT '0',
    AVG_AVG             NUMERIC(13,2) DEFAULT '0'
);


CREATE TABLE STANDARD_TEST_SUMMARY
(
    PER_TEST_ID                 INTEGER,
    DATA_CATEGORY               CHAR(1),
    CONNECT_TYPE                CHAR(5),
    DATA_SCALE                  VARCHAR(10),
    INTERFACE                   CHAR(30),
    TEST_ITEM                   CHAR(50),
    TEST_START_TIME             DATE,
    TEST_END_TIME               DATE,
    INSERT_AVG                  NUMERIC(10,2),
    UPDATE_AVG                  NUMERIC(10,2),
    SELECT_AVG                  NUMERIC(10,2),
    DELETE_AVG                  NUMERIC(10,2),
    INSERT_SELECT_AVG           NUMERIC(10,2),
    SELECT_UPDATE_AVG           NUMERIC(10,2),
    INSERT_SELECT_UPDATE_AVG    NUMERIC(10,2),
    COMMENT                     VARCHAR(32000),
    MODIFIER                    CHAR(50),
    THREAD                      INTEGER,
    NODE_ID                     CHAR(10),
    LATENCY_AVG                 NUMERIC(13,2),
    MIN_AVG                     NUMERIC(13,2),
    MAX_AVG                     NUMERIC(13,2),
    AVG_AVG                     NUMERIC(13,2)
);


CREATE SEQUENCE PERTESTID
START WITH 1
MINVALUE 1
MAXVALUE 9223372036854775806;