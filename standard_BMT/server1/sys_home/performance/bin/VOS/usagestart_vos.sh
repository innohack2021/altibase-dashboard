rm -f ./usage_collect
while true
do
DBPID=`ps -ef | grep '^  altibase' | grep altibase.pm | grep -v grep | awk '{print $2}'`
./topb -p $DBPID | grep altibase | awk '{print $2, $3}' >> ./usage_collect
sleep 1
done
