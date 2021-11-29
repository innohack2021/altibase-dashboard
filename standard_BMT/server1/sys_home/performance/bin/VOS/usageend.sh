kill -15 `ps -ef | grep $USER | grep usagestart_vos.sh | grep -v grep | awk '{print $2}'`
cat ./usage_collect | awk '{printf " %.2f, %.2f\n", (sum1+=$1)/NR, ((sum2+=$2)/NR)*4096/1024/1024}' | tail -1 >> ./usage_result
