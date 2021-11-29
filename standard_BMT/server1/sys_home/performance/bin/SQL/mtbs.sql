set linesize 1024
set colsize 25

--- memory tablespace
SELECT --TBS_ID
     --, TBS_TYPE
       '['||TO_CHAR(SYSDATE, 'YYYY-MM-DD HH:MI:SS')||']' TIME, TBS_NAME
     , TO_CHAR(MAX/1024/1024, '999,999,999') 'MAX(M)'
     , TO_CHAR(TOTAL/1024/1024, '999,999,999') 'TOTAL(M)'
     , TO_CHAR(ALLOC/1024/1024, '999,999,999') 'ALLOC(M)'
     , TO_CHAR(USED/1024/1024, '999,999,999') 'USED(M)'
     --, TO_CHAR((ROUND((USED/1024/1024), 0)/ROUND((TOTAL/1024/1024), 0))*100, '999.99') 'USAGE(%)'
     --, STATE
     , AUTOEXTEND
  FROM (SELECT ID TBS_ID
             , DECODE(TYPE, 0, 'MEM_SYS_DIC', 1, 'MEM_SYS_DATA', 2, 'MEM_USER_DATA', 8, 'VOL_USER_DATA') TBS_TYPE
             , NAME TBS_NAME
             , DECODE(M.MAXSIZE, 140737488322560, D.MEM_MAX_DB_SIZE , 0 , T.TOTAL_PAGE_COUNT * T.PAGE_SIZE, M.MAXSIZE) MAX
             , M.ALLOC_PAGE_COUNT * T.PAGE_SIZE TOTAL
             , NVL(M.ALLOC_PAGE_COUNT-M.FREE_PAGE_COUNT, T.TOTAL_PAGE_COUNT)*PAGE_SIZE ALLOC
             , NVL(MT.USED, 0) USED
             , DECODE(T.STATE, 1, 'OFFLINE', 2, 'ONLINE', 5, 'OFFLINE BACKUP', 6, 'ONLINE BACKUP', 128, 'DROPPED', 'DISCARDED') STATE
             , DECODE(M.AUTOEXTEND_MODE, 1, 'ON', 'OFF') 'AUTOEXTEND'
          FROM V$DATABASE D
             , V$TABLESPACES T
             , (SELECT SPACE_ID
                     , SPACE_NAME
                     , ALLOC_PAGE_COUNT
                     , FREE_PAGE_COUNT
                     , DECODE(MAX_SIZE, 0, (SELECT VALUE1
                                              FROM V$PROPERTY
                                              WHERE NAME = 'VOLATILE_MAX_DB_SIZE'), MAX_SIZE) AS MAXSIZE
                     , AUTOEXTEND_MODE
                  FROM V$VOL_TABLESPACES
                 UNION ALL
                SELECT SPACE_ID
                     , SPACE_NAME
                     , ALLOC_PAGE_COUNT
                     , FREE_PAGE_COUNT
                     , MAXSIZE
                     , AUTOEXTEND_MODE
                  FROM V$MEM_TABLESPACES ) M LEFT OUTER JOIN (SELECT TABLESPACE_ID, SUM((FIXED_USED_MEM + VAR_USED_MEM)) USED
                                                                FROM V$MEMTBL_INFO
                                                               GROUP BY TABLESPACE_ID ) MT ON M.SPACE_ID = MT.TABLESPACE_ID
         WHERE T.ID = M.SPACE_ID) ;

---select  
SELECT '['||TO_CHAR(SYSDATE, 'YYYY-MM-DD HH:MI:SS')||']' TIME, 'TEST', COUNT(*) FROM TEST;
