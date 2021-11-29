//#define TEST_MODE "Insert"


#define SQL_LEN 1000
void print_diagnostic(SQLSMALLINT aHandleType, SQLHANDLE aHandle)
{
    SQLRETURN   rc;
    SQLSMALLINT sRecordNo;
    SQLCHAR     sSQLSTATE[6];
    SQLCHAR     sMessage[2048];
    SQLSMALLINT sMessageLength;
    SQLINTEGER  sNativeError;

    sRecordNo = 1;

    while ((rc = SQLGetDiagRec(aHandleType,
                               aHandle,
                               sRecordNo,
                               sSQLSTATE,
                               &sNativeError,
                               sMessage,
                               sizeof(sMessage),
                               &sMessageLength)) != SQL_NO_DATA)
    {
        printf("Diagnostic Record %d\n", sRecordNo);
        printf("     SQLSTATE     : %s\n", sSQLSTATE);
        printf("     Message text : %s\n", sMessage);
        printf("     Message len  : %d\n", sMessageLength);
        printf("     Native error : 0x%X\n", sNativeError);

        if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
        {
            break;
        }

        sRecordNo++;
    }
}

void execute_err(SQLHDBC aCon, SQLHSTMT aStmt, char* q)
{
    printf("Error : %s\n",q);

    if (aStmt == SQL_NULL_HSTMT)
    {
        if (aCon != SQL_NULL_HDBC)
        {
            print_diagnostic(SQL_HANDLE_DBC, aCon);
        }
    }
    else
    {
        print_diagnostic(SQL_HANDLE_STMT, aStmt);
    }
}
void* worker ( void* argument ) {
    
    char           connection[1024];
    char         query[SQL_LEN];
    SQLHENV        env;
    SQLHDBC        dbc;
    SQLHSTMT       stmt;
    SQLLEN       row_count;
    SQLLEN       totalRowcount;
    int            k01;
    char   k02[12];
    char   k03[12];
    char   k04[11];
    char   k05[11];
    char   k06[11];
    char   k07[21];
    char   k08[21];
    char   k09[21];
    char   k10[21];
    double k11;
    double k12;
    double k13;
    char   k14[11];
    char   k15[51];
    char   k16[51];
    char   k17[51];
    char   k18[51];
    int    k19;
    int    k20;
    char   k21[4];
    char   k22[4];
    char   k23[11];
    int    k24;
    int    k25;
    int    k26;
    int    k27;
    char   k28[31];
    char   k29[31];
    char   k30[31];
    char   k31[12];
    double k32;
    double k33;
    int    k34;
    int    k35;
    char   k36[11];
    char   k37[11];
    char   k38[101];
    char   k39[101];
    char   k40[101];
    int    k41;
    int    k42;
    int    k43;
    double k44;
    double k45;
    char   k46[11];
    char   k47[11];
    char   k48[12];
    char   k49[12];
    char   k50[21];
    char   k51[12];
    int    k52;
    int    k53;
    char   k54[12];
    char   k55[21];
    char   k56[21];
    char   k57[21];
    double k58;
    int    k59;
    char   k60[301];

    int            start;
    int            end;
    int            value;
    int		   dvalue;
    struct timeval startTime;
    struct timeval endTime;
    int            elapsed;

    dvalue = 12345.67809;

    k11 = dvalue;
    k12 = dvalue;
    k13 = dvalue;
    k32 = dvalue;
    k33 = dvalue;
    k44 = dvalue;
    k45 = dvalue;
    k58 = dvalue;
    
    memset( k02, 0, sizeof(k02) );
    memset( k03, 0, sizeof(k03) );
    memset( k04, 0, sizeof(k04) );
    memset( k05, 0, sizeof(k05) );
    memset( k06, 0, sizeof(k06) );
    memset( k07, 0, sizeof(k07) );
    memset( k08, 0, sizeof(k08) );
    memset( k09, 0, sizeof(k09) );
    memset( k10, 0, sizeof(k10) );
    memset( k14, 0, sizeof(k14) );
    memset( k15, 0, sizeof(k15) );
    memset( k16, 0, sizeof(k16) );
    memset( k17, 0, sizeof(k17) );
    memset( k18, 0, sizeof(k18) );
    memset( k21, 0, sizeof(k21) );
    memset( k22, 0, sizeof(k22) );
    memset( k23, 0, sizeof(k23) );
    memset( k28, 0, sizeof(k28) );
    memset( k29, 0, sizeof(k29) );
    memset( k30, 0, sizeof(k30) );
    memset( k31, 0, sizeof(k31) );
    memset( k36, 0, sizeof(k36) );
    memset( k37, 0, sizeof(k37) );
    memset( k38, 0, sizeof(k38) );
    memset( k39, 0, sizeof(k39) );
    memset( k40, 0, sizeof(k40) );
    memset( k46, 0, sizeof(k46) );
    memset( k47, 0, sizeof(k47) );
    memset( k48, 0, sizeof(k48) );
    memset( k49, 0, sizeof(k49) );
    memset( k50, 0, sizeof(k50) );
    memset( k51, 0, sizeof(k51) );
    memset( k54, 0, sizeof(k54) );
    memset( k55, 0, sizeof(k55) );
    memset( k56, 0, sizeof(k56) );
    memset( k57, 0, sizeof(k57) );
    memset( k60, 0, sizeof(k60) );
    strcpy( k02, "22-DEC-2014" );
    strcpy( k03, "22-DEC-2014" );
    strcpy( k04, "abcdefghij" );
    strcpy( k05, "abcdefghij" );
    strcpy( k06, "abcdefghij" );
    strcpy( k07, "abcdefghijklmnopq" );
    strcpy( k08, "abcdefghijklmnopqr" );
    strcpy( k09, "abcdefghijklmnopqrs" );
    strcpy( k10, "abcdefghijklmnopqrst" );
    strcpy( k14, "abcdefghij" );
    strcpy( k15, "abcdefghijklmnopqrst          abcdefghijklmnopqrst" );
    strcpy( k16, "abcdefghijklmnopqrst     abcdefghijklmnopqrst" );
    strcpy( k17, "     abcdefghijklmnopqrst     abcdefghijklmnopqrst" );
    strcpy( k18, " abcdefghijklmnopqrst        abcdefghijklmnopqrst " );
    strcpy( k21, "abs" );
    strcpy( k22, "xyz" );
    strcpy( k23, "abcdefghij" );
    strcpy( k28, "abcdefghijklmnopqrstuvwxyz0123" );
    strcpy( k29, "abcdefghijklmnopqrstuvwxyz0123" );
    strcpy( k30, "abcdefghijklmnopqrstuvwxyz0123" );
    strcpy( k31, "22-DEC-2014" );
    strcpy( k36, "abcdefghij" );
    strcpy( k37, "abcdefghij" );
    strcpy( k38, "abcdefghijklmnopqrstuvwxyz0123abcdefghijklmnopqrstuvwxyz0123abcdefghijklmnopqrstuvwxyz01230123456789" );
    strcpy( k39, "abcdefghijklmnopqrstuvwxyz0123abcdefghijklmnopqrstuvwxyz0123abcdefghijklmnopqrstuvwxyz01230123456789" );
    strcpy( k40, "abcdefghijklmnopqrstuvwxyz0123abcdefghijklmnopqrstuvwxyz0123abcdefghijklmnopqrstuvwxyz01230123456789" );
    strcpy( k46, "abcdefghij" );
    strcpy( k47, "abcdefghij" );
    strcpy( k48, "22-DEC-2014" );
    strcpy( k49, "22-DEC-2014" );
    strcpy( k50, "abcdefghijklmnopqrst" );
    strcpy( k51, "22-DEC-2014" );
    strcpy( k54, "22-DEC-2014" );
    strcpy( k55, "abcdefghijklmnopqrst" );
    strcpy( k56, "abcdefghijklmnopqrst" );
    strcpy( k57, "abcdefghijklmnopqrst" );
    strcpy( k60, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz1234567890okOK" );

    threadContext* context = (threadContext*)argument;
    
    sprintf( connection, "%s;UID=%s;PWD=%s", option, user, password );
    
    assert( SQLAllocEnv( &env ) == SQL_SUCCESS );
    
    assert( SQLAllocConnect( env, &dbc ) == SQL_SUCCESS );
    
    assert( SQLDriverConnect( dbc, NULL, connection, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT ) == SQL_SUCCESS );
    
    assert( SQLAllocStmt( dbc, &stmt ) == SQL_SUCCESS );
    sprintf(query,"INSERT INTO TEST VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ? )");
    
    if (SQLPrepare(stmt, (SQLCHAR *)query, SQL_NTS) != SQL_SUCCESS)
    {
        execute_err(dbc, stmt, query);
        SQLFreeStmt(stmt, SQL_DROP);
        return SQL_ERROR;
    }
    
    assert( SQLBindParameter( stmt,  1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k01, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  11, 0, &k02, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  11, 0, &k03, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  10, 0, &k04, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  10, 0, &k05, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  10, 0, &k06, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  7, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  20, 0, &k07, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  8, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  20, 0, &k08, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt,  9, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  20, 0, &k09, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 10, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  20, 0, &k10, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 11, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k11, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 12, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k12, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 13, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k13, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 14, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  10, 0, &k14, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 15, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  50, 0, &k15, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 16, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  50, 0, &k16, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 17, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  50, 0, &k17, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 18, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  50, 0, &k18, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 19, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k19, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 20, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k20, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 21, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  3, 0, &k21, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 22, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  3, 0, &k22, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 23, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  3, 0, &k23, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 24, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k24, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 25, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k25, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 26, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k26, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 27, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k27, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 28, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  30, 0, &k28, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 29, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  30, 0, &k29, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 30, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  30, 0, &k30, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 31, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  11, 0, &k31, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 32, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k32, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 33, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k33, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 34, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k34, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 35, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k35, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 36, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  10, 0, &k36, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 37, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,  10, 0, &k37, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 38, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  100, 0, &k38, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 39, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  100, 0, &k39, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 40, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,  100, 0, &k40, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 41, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k41, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 42, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k42, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 43, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &k43, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 44, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k44, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 45, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_DOUBLE,  0, 0, &k45, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 46, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 10, 0, &k46, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 47, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 10, 0, &k47, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 48, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 11, 0, &k48, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 49, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 11, 0, &k49, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 50, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 20, 0, &k50, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 51, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 11, 0, &k51, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 52, SQL_PARAM_INPUT, SQL_C_SLONG,  SQL_INTEGER, 30, 0, &k52, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 53, SQL_PARAM_INPUT, SQL_C_SLONG,  SQL_INTEGER, 30, 0, &k53, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 54, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 11, 0, &k54, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 55, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 20, 0, &k55, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 56, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 20, 0, &k56, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 57, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_CHAR, 20, 0, &k57, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 58, SQL_PARAM_INPUT, SQL_C_DOUBLE,  SQL_DOUBLE, 0, 0, &k58, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 59, SQL_PARAM_INPUT, SQL_C_SLONG,  SQL_INTEGER, 0, 0, &k59, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindParameter( stmt, 60, SQL_PARAM_INPUT, SQL_C_CHAR,  SQL_VARCHAR, 300, 0, &k60, 0, NULL ) == SQL_SUCCESS );
    
    assert( pthread_mutex_unlock( &(context->connected) ) == 0 );
    
    while ( allocateUnit( &start, &end ) > 0 ) {
        
        for ( value = start; value < end; value++ ) {
            
            assert( gettimeofday( &startTime, NULL ) == 0 );
            
            k01 = value;
            k19 = value;
            k20 = value;
            k24 = value;
            k25 = value;
            k26 = value;
            k27 = value;
            k34 = value;
            k35 = value;
            k41 = value;
            k42 = value;
            k43 = value;
            k52 = value;
            k53 = value;
            k59 = value;
           if ( SQLExecute(stmt) != SQL_SUCCESS )
           {
               execute_err(dbc, stmt, query);
               SQLFreeStmt(stmt, SQL_DROP);
               return SQL_ERROR;
           }
           else
           {
           } 
            assert( gettimeofday( &endTime, NULL ) == 0 );
            if ( endTime.tv_usec > startTime.tv_usec ) {
                elapsed = ( endTime.tv_sec  - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec - startTime.tv_usec );
            } else {
                elapsed = ( endTime.tv_sec  - 1 - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec + 1000000 - startTime.tv_usec );
            }
            
            if ( context->minimum > elapsed ) context->minimum = elapsed;
            if ( context->maximum < elapsed ) context->maximum = elapsed;
            context->sum += elapsed;
            context->numberOfTransactions++;
            if ( elapsed >= threshold ) context->numberOfLongTransactions++;
            
        }
        
    }
    
    assert( SQLFreeStmt( stmt, SQL_DROP ) == SQL_SUCCESS );
    
    assert( SQLDisconnect( dbc ) == SQL_SUCCESS );
    
    assert( SQLFreeConnect( dbc ) == SQL_SUCCESS );
    
    assert( SQLFreeEnv( env ) == SQL_SUCCESS );    
    
    return argument;
    
}
