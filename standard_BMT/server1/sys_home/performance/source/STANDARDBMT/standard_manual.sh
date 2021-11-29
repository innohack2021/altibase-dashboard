#set -x
cd $HOME/performance/source/STANDARDBMT
. set_test.env

GIGA="774705"
let PORTION=$ISR_INSERT_RATIO*4+$ISUR_INSERT_RATIO*4+500
COUNTS=$(echo "$GIGA $PORTION 100" | awk '{print int($1/$2*$3)}')

if [ $MVOLUME ]
then
    let SCALE=$MVOLUME*COUNTS
    export SCALE
else
    export SCALE=$4
fi

export STORAGE=$3
export TESTNAME=$1"-"$2
echo $TESTNAME

cd "$STANDARD_WORK/$1/$2/$3"
echo "$STANDARD_WORK/$1/$2/$3"

if [ $1 == "TIMESTEN" ]
then
./runcs.sh > $STANDARD_LOG/manual_$STANDARD_DATE.log
else
./run.sh > $STANDARD_LOG/manual_$STANDARD_DATE.log
fi

cd $STANDARD_RESULT
echo $2
#if [ "$3" = "DISK" ] &&[ "$2" = "SQLCLI" ]
#then 
#     ./final-disk.sh $3
#elif [ "$2" = "APRE" ]
#then
#     ./final-apre.sh $3
#else 
     ./final-memory.sh $3 
#fi
