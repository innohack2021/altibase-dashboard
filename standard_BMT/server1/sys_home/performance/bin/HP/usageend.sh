WHOAMI=`whoami`
kill -9 `ps -ef | grep $WHOAMI | grep usagestart.sh | grep -v grep | awk '{print $2}'`

cat ./top.log | grep altibase | awk '{printf " %.2f, %.2f\n", (sum2+=$2)/NR, (sum3+=$3)/NR}' | tail -1 >> ./usage_result
