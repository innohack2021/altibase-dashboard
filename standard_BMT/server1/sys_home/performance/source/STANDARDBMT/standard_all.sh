source ./set_test.env

GIGA="774705"

let COUNT_PERCENTAGE=$THREADS_COUNT*100
let PORTION=$ISR_INSERT_RATIO*4+$ISUR_INSERT_RATIO*4+$COUNT_PERCENTAGE
COUNTS=$(echo "$GIGA $PORTION 100" | awk '{print int($1/$2*$3)}')

if [ $VOLUME ];
then
    let SCALE=$VOLUME*$COUNTS
    export SCALE
fi

#HDB_PATH="$HDB_APRE $HDB_JDBC $HDB_SQLCLI"
HDB_PATH="$HDB_APRE"
XDB_PATH="$XDB_APRE $XDB_SQLCLI"
ORACLE_PATH="$ORACLE_PROC $ORACLE_JDBC $ORACLE_OCI"

if [ $1 = "HDB" ]
then
    TEST_PATH=$HDB_PATH
elif [ $1 = "XDB" ]
then
    TEST_PATH=$XDB_PATH
elif [ $1 = "ORACLE" ]
then
    TEST_PATH=$ORACLE_PATH
else
    echo "Error product name"
    echo "Support HDB, XDB, ORACLE"
fi

cd $STANDARD_RESULT

for TEST_PATH in $TEST_PATH
do
	cd $TEST_PATH
	./run.sh >> $STANDARD_LOG/standard_$STANDARD_DATE.log
done

cd $STANDARD_RESULT
./final.sh
