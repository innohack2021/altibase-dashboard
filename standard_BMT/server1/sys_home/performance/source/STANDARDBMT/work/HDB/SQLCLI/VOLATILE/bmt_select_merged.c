#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <sqlcli.h>

typedef struct threadContext {
    pthread_mutex_t connected;
    char            connection[1024];
    int             minimum;
    int             maximum;
    long long       sum;
    int             numberOfTransactions;
    int             numberOfLongTransactions;
} threadContext;

int numberOfThreads;
int startValue;
int numberOfTransactions;
int sizeOfUnit;
int threshold;
int cap;

struct timeval connectTime;
struct timeval startTime;
struct timeval endTime;

pthread_mutex_t* mutex;
int*             remain;
int*             cursor;
int*             allocated;

char user[1024];
char password[1024];
char option[1024];
char test_mode[1024];

int compareThreadContexts ( const void* element1, const void* element2 ) {
    
    const threadContext* context1;
    const threadContext* context2;
    
    context1 = (const threadContext*)element1;
    context2 = (const threadContext*)element2;
    
    if ( context1->numberOfTransactions < context2->numberOfTransactions ) return -1;
    if ( context1->numberOfTransactions > context2->numberOfTransactions ) return  1;
    
    return 0;
    
}

int allocateUnit ( int* start, int* end ) {
    
    int size;
    int elapsed;
    
    assert( pthread_mutex_lock( mutex ) == 0 );
    
    if ( cap > 0 ) {
        assert( gettimeofday( &endTime, NULL ) == 0 );
        if ( endTime.tv_usec > startTime.tv_usec ) {
            elapsed = ( endTime.tv_sec  - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec - startTime.tv_usec );
        } else {
            elapsed = ( endTime.tv_sec  - 1 - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec + 1000000 - startTime.tv_usec );
        }
        while ( (double)(*allocated) / ( (double)elapsed / 1000000. ) > (double)cap ) {
            sched_yield();
            assert( gettimeofday( &endTime, NULL ) == 0 );
            if ( endTime.tv_usec > startTime.tv_usec ) {
                elapsed = ( endTime.tv_sec  - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec - startTime.tv_usec );
            } else {
                elapsed = ( endTime.tv_sec  - 1 - startTime.tv_sec ) * 1000000 + ( endTime.tv_usec + 1000000 - startTime.tv_usec );
            }
        }
    }
    
    if ( (*remain) > sizeOfUnit ) {
        size       = sizeOfUnit;
        (*remain) -= sizeOfUnit;
    } else {
        size       = (*remain);
        (*remain) -= (*remain);
    }
    *start        = (*cursor);
    *end          = (*cursor) + size;
    (*cursor)    += size;
    (*allocated) += size;
    
    assert( pthread_mutex_unlock( mutex ) == 0 );
    
    return size;
      
}

char* workingDirectory() {
    
    static char buffer[4096];
    
    char* directory;
    char* home;
    
    directory = getcwd( buffer, sizeof(buffer) - 1 );
    home      = getenv( "STANDARD_WORK" );
    
    assert( directory != NULL );
    if ( home != NULL ) {
        if ( strncmp( directory, home, strlen( home ) ) == 0 ) {
            directory += strlen( home );
        }
    }
    while( *directory == '/' || *directory == '\\' ) {
        directory++;
    }
    
    return directory;
        
}

void writeResult( char* mode, int dimension, int axis1, double axis2 ) {
    
    char* result;
    char* date;
    char* host;
    char* revision;
    char  filename[4096];
    FILE* file;
    
    result = getenv( "STANDARD_RESULT" );
    
    if ( result != NULL ) {
        
        date = getenv( "STANDARD_DATE" );
        if ( date == NULL ) {
            date = "YYYYMMDD";
        }
        host = getenv( "STANDARD_HOST" );
        if ( host == NULL ) {
            host = "NOHOST";
        }
        revision = getenv( "STANDARD_REVISION" );
        if ( revision == NULL ) {
            revision = "0";
        }
        
	sprintf( filename, "%s/%s_HDB-SQLCLI_%s.sql", result, host, date );
        file = fopen( filename, "a" );
        assert( file != NULL );
        
        switch ( dimension ) {
         case 1:
            break;
         case 2:
            fprintf( file, "%s, %s, %s, %s, %s, %d, %f \n", date, workingDirectory(), mode, host, revision, axis1, axis2 );
            break;
         default:
            assert( dimension == 1 || dimension == 2 ) ;
            break;
        }
        
        assert( fclose( file ) == 0 );
        
    }
    
}
//#define TEST_MODE "Select"

void* worker ( void* argument ) {
    
    char           connection[1024];
    SQLHENV        env;
    SQLHDBC        dbc;
    SQLHSTMT       stmt;
    int            p01;
    int            k01;
    char           k02[12];
    char           k04[11];
    char           k07[21];
    double         k11;
    char           k15[51];
    char           k21[4];
    char           k28[31];
    char           k38[101];
    int            k59;
    
    int            start;
    int            end;
    int            value;
    struct timeval startTime;
    struct timeval endTime;
    int            elapsed;
    
    threadContext* context = (threadContext*)argument;
    
    sprintf( connection, "%s;UID=%s;PWD=%s", option, user, password );
    
    assert( SQLAllocEnv( &env ) == SQL_SUCCESS );
    
    assert( SQLAllocConnect( env, &dbc ) == SQL_SUCCESS );
    
    assert( SQLDriverConnect( dbc, NULL, connection, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT ) == SQL_SUCCESS );
    
    assert( SQLAllocStmt( dbc, &stmt ) == SQL_SUCCESS );
    
    assert( SQLPrepare( stmt, "SELECT K01, K02, K04, K07, K11, K15, K21, K28, K38, K59 FROM TEST WHERE K01 = ?", SQL_NTS ) == SQL_SUCCESS );
    
    assert( SQLBindParameter( stmt,  1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER,  0, 0, &p01, 0, NULL ) == SQL_SUCCESS );
    
    assert( SQLBindCol( stmt,  1, SQL_C_SLONG, &k01, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  2, SQL_C_CHAR, k02, sizeof(k02), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  3, SQL_C_CHAR, k04, sizeof(k04), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  4, SQL_C_CHAR, k07, sizeof(k07), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  5, SQL_C_DOUBLE, &k11, 0, NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  6, SQL_C_CHAR, k15, sizeof(k15), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  7, SQL_C_CHAR, k21, sizeof(k21), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  8, SQL_C_CHAR, k28, sizeof(k28), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  9, SQL_C_CHAR, k38, sizeof(k38), NULL ) == SQL_SUCCESS );
    assert( SQLBindCol( stmt,  10, SQL_C_SLONG, &k59, 0, NULL ) == SQL_SUCCESS );
    
    assert( pthread_mutex_unlock( &(context->connected) ) == 0 );
    
    while ( allocateUnit( &start, &end ) > 0 ) {
        
        for ( value = start; value < end; value++ ) {
            
            assert( gettimeofday( &startTime, NULL ) == 0 );
            
            p01 = value;
            
            assert( SQLExecute( stmt ) == SQL_SUCCESS );
            
            while( SQLFetch( stmt ) == SQL_SUCCESS );
            
            assert( SQLFreeStmt( stmt, SQL_CLOSE ) == SQL_SUCCESS );
            
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

int main( int argc, char* argv[] ) {
    
    threadContext*      contexts;
    pthread_attr_t      threadAttribute;
    int                 thread;
    pthread_t*          threads;
    void*               value;
    struct tm*          tm;
    long long           second;
    long long           usecond;
    long long           elapsed;
    double              tps;
    int                 minimum;
    int                 maximum;
    long long           sum;
    int                 numberOfLongTransactions;
    int                 average;

    cap = 0;

    switch( argc ) {
     case 10:
        strcpy( option,        argv[9] );
     case 9:
        strcpy( password,      argv[8] );
     case 8:
        strcpy( user,          argv[7] );
     case 7:
        strcpy( test_mode,     argv[6] );
     case 6:
        threshold            = atoi( argv[5] );
     case 5:
        sizeOfUnit           = atoi( argv[4] );
     case 4:
        numberOfTransactions = atoi( argv[3] );
     case 3:
        startValue           = atoi( argv[2] );
     case 2:
        numberOfThreads      = atoi( argv[1] );
        break;
     default:
        printf( "Usage: %s numberOfThreads [startValue] [numberOfTransactions] [sizeOfUnit] [threshold] [test_mode] [user] [password] [option]\n", argv[0] );
        exit( EXIT_FAILURE );
        break;
    }
    
    printf( "Working Directory                 : %s\n",  workingDirectory()   );
    printf( "Test Mode                         : %s\n",  test_mode            );
    printf( "Number of Threads                 : %8d\n", numberOfThreads      );
    printf( "Start Value                       : %8d\n", startValue           );
    printf( "Number of Transactions            : %8d\n", numberOfTransactions );
    printf( "Size   of Unit                    : %8d\n", sizeOfUnit           );
    printf( "Threshold(microsecond)            : %8d\n", threshold            );
    printf( "Cap(TPS)                          : %8d\n", cap                  );
    printf( "User                              : %s\n",  user                 );
    printf( "Password                          : %s\n",  password             );
    printf( "Option                            : %s\n",  option               );
    
    contexts = malloc( sizeof(threadContext) * numberOfThreads );
    assert( contexts != NULL );
    memset( contexts, 0, sizeof(threadContext) * numberOfThreads );
    for ( thread = 0; thread < numberOfThreads; thread++ ) {
        assert( pthread_mutex_init( &(contexts[thread].connected), NULL ) == 0 );
        sprintf( contexts[thread].connection, "%d", thread );
        contexts[thread].minimum                  = INT_MAX;
        contexts[thread].maximum                  = 0;
        contexts[thread].sum                      = 0;
        contexts[thread].numberOfTransactions     = 0;
        contexts[thread].numberOfLongTransactions = 0;
    }
    
    threads = malloc( sizeof(pthread_t) * numberOfThreads );
    assert( threads != NULL );
    
    mutex = malloc( sizeof(pthread_mutex_t) );
    assert( mutex != NULL );
    remain = malloc( sizeof(int) );
    assert( remain != NULL );
    cursor = malloc( sizeof(int) );
    assert( cursor != NULL );
    allocated = malloc( sizeof(int) );
    assert( allocated != NULL );
    
    assert( pthread_mutex_init( mutex, NULL ) == 0 );
    
    *remain    = numberOfTransactions;
    *cursor    = startValue;
    *allocated = 0;
    
    assert( pthread_attr_init( &threadAttribute ) == 0 );
    assert( pthread_attr_setscope( &threadAttribute, PTHREAD_SCOPE_SYSTEM ) == 0 );
    
    fflush( stdout );
    fflush( stderr );

    assert( gettimeofday( &connectTime, NULL ) == 0 );

    assert( pthread_mutex_lock( mutex ) == 0 );

    for ( thread = 0; thread < numberOfThreads; thread++ ) {
        assert( pthread_mutex_lock( &(contexts[thread].connected) ) == 0 );
        assert( pthread_create( threads + thread, &threadAttribute, worker, contexts + thread ) == 0 );
    }

    for ( thread = 0; thread < numberOfThreads; thread++ ) {
        assert( pthread_mutex_lock( &(contexts[thread].connected) ) == 0 );
        assert( pthread_mutex_unlock( &(contexts[thread].connected) ) == 0 );
    }

    assert( gettimeofday( &startTime, NULL ) == 0 );
    if ( startTime.tv_usec > connectTime.tv_usec ) {
        second  = startTime.tv_sec  - connectTime.tv_sec;
        usecond = startTime.tv_usec - connectTime.tv_usec;
    } else {
        second  = startTime.tv_sec  -       1 - connectTime.tv_sec;
        usecond = startTime.tv_usec + 1000000 - connectTime.tv_usec;
    }
    printf( "Connection Elapsed                : %llu.%06llu second\n", second, usecond );
    tm = localtime( &(startTime.tv_sec) );
    printf( "Start Time                        : %04u/%02u/%02u %02u:%02u:%02u.%06u\n", (unsigned int)(1900+tm->tm_year), (unsigned int)(tm->tm_mon+1), (unsigned int)(tm->tm_mday), (unsigned int)(tm->tm_hour), (unsigned int)(tm->tm_min), (unsigned int)(tm->tm_sec), (unsigned int)(startTime.tv_usec) );
    
    assert( pthread_mutex_unlock( mutex ) == 0 );
    
    fflush( stdout );
    fflush( stderr );
    
    for ( thread = 0; thread < numberOfThreads; thread++ ) {
        assert( pthread_join( threads[thread], &value ) == 0 );
    }
    
    assert( gettimeofday( &endTime, NULL ) == 0 );
    tm = localtime( &(endTime.tv_sec) );
    printf( "End   Time                        : %04u/%02u/%02u %02u:%02u:%02u.%06u\n", (unsigned int)(1900+tm->tm_year), (unsigned int)(tm->tm_mon+1), (unsigned int)(tm->tm_mday), (unsigned int)(tm->tm_hour), (unsigned int)(tm->tm_min), (unsigned int)(tm->tm_sec), (unsigned int)(endTime.tv_usec) );
    
    assert( pthread_attr_destroy( &threadAttribute ) == 0 );
    
    assert( pthread_mutex_destroy( mutex ) == 0 );
    
    qsort( contexts, numberOfThreads, sizeof(threadContext), compareThreadContexts );
    
    minimum                  = INT_MAX;
    maximum                  = 0;
    sum                      = 0;
    numberOfLongTransactions = 0;
    for ( thread = 0; thread < numberOfThreads; thread++ ) {
        if ( minimum > contexts[thread].minimum ) minimum = contexts[thread].minimum;
        if ( maximum < contexts[thread].maximum ) maximum = contexts[thread].maximum;
        sum                      += contexts[thread].sum;
        numberOfLongTransactions += contexts[thread].numberOfLongTransactions;
    }
    average = (int)( (double)sum / (double)numberOfTransactions );
    
    if ( endTime.tv_usec > startTime.tv_usec ) {
        second  = endTime.tv_sec  - startTime.tv_sec;
        usecond = endTime.tv_usec - startTime.tv_usec;
    } else {
        second  = endTime.tv_sec  -       1 - startTime.tv_sec;
        usecond = endTime.tv_usec + 1000000 - startTime.tv_usec;
    }
    printf( "Elapsed                           : %llu.%06llu second\n", second, usecond );
    
    elapsed = second * 1000000 + usecond;
    tps = (double)numberOfTransactions / ( (double)elapsed / 1e6 );
    printf( "Transactions per Second           : %9.2f TPS\n", tps );
    printf( "Minimum                           : %6d microseconds\n", minimum );
    printf( "Maximum                           : %6d microseconds\n", maximum );
    printf( "Average                           : %6d microseconds\n", average );
    printf( "Number of Long Transactions       : %6.2f%% ( %d / %d )\n", (double)numberOfLongTransactions / (double)numberOfTransactions * 100, numberOfLongTransactions, numberOfTransactions );
    printf( "Number of Transactions per Thread :" );
    for ( thread = 0; thread < numberOfThreads; thread++ ) {
        printf( " %d", contexts[thread].numberOfTransactions );
    }
    printf( "\n" );
    printf( "\n" );
    
    writeResult( test_mode, 2, numberOfThreads, tps );
    
    return EXIT_SUCCESS;
    
}