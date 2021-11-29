rm -f ./usage_collect
WHOAMI=`whoami`
INTERVAL=0.5
DBPID=`ps -ef | grep $WHOAMI | grep "altibase -p" | grep -v grep | awk '{print $2}'`
top -d $INTERVAL -p $DBPID -b > ./usage_collect &
