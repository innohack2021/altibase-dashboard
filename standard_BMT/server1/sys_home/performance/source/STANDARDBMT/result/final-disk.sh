#!/bin/bash
if [ "$TESTNAME" ];
then
    TESTCASE="$TESTNAME"
else
    TESTCASE="HDB-APRE HDB-JDBC HDB-SQLCLI"
#    TESTCASE="XDB-APRE XDB-SQLCLI"
fi


rm -f test_result
rm -f final_result
count=1
ISURec=1
ISRec=1
SURec=1

for TESTCASE in $TESTCASE
do
    while read line
    do
        echo "inputline="$line
        if [[ $line == *Insert+Select+Update,* ]]; then
            echo $ISURec
	    if [ $(($ISURec%3)) == 0 ]; then
                let count=$count+2
		echo "%3=0"$count
		sed -n "$count"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{print $1, $2, $3, $4, $5, $6, $7}' > result1
		let ISURec=$ISURec+1
	     else
	         echo "%3!=0"
	         let ISURec=$ISURec+1
	         echo $ISURec
	         continue
	     fi
		let j=$count-2
		echo "insert+select+update"$count$j
		sed -n "$j","$count"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{ sum9+=$9; sum10+=$10; sum11+=$11; sum12+=$12; sum13+=$13 } END {printf "%.2f, %.2f, %d, %d, %d\n", sum9, sum10, sum11, sum12, sum13}' > result2
		paste -d' '  result1 result2 >> test_result_$STANDARD_DATE
        elif [[ $line == *Insert+Select,* ]]; then
		echo $ISRec
		if [ $(($ISRec%2)) == 0 ]; then
		    (( count++ ))
		    echo "%2==0"$count
		    sed -n "$count"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{print $1, $2, $3, $4, $5, $6, $7}' > result1
		    let ISRec=$ISRec+1
		else
		    echo "%2!=0"
		    let ISRec=$ISRec+1
		    echo $ISRec
		    continue
		fi
		let j=$count-1
		echo "insert+select"$count$j
		sed -n "$j","$count"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{ sum9+=$9; sum10+=$10; sum11+=$11; sum12+=$12; sum13+=$13 } END {printf "%.2f, %.2f, %d, %d, %d\n", sum9, sum10, sum11, sum12, sum13}' > result2
		paste -d' '  result1 result2 >> test_result_$STANDARD_DATE
        elif [[ $line == *Select+Update,* ]]; then
		echo $SURec
		if [ $(($SURec%2)) == 0 ]; then
		    (( count++ ))
		    echo "%2==0"$count
		    sed -n "$count"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{print $1, $2, $3, $4, $5, $6, $7}' > result1
		    let SURec=$SURec+1
		else
		    echo "%2!=0"
		    let SURec=$SURec+1
		    echo $SURec
		    continue
		fi
		let j=$count-1
		echo "select+update"$count$j
		sed -n "$j","$count"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{ sum9+=$9; sum10+=$10; sum11+=$11; sum12+=$12; sum13+=$13 } END {printf "%.2f, %.2f, %d, %d, %d\n", sum9, sum10, sum11, sum12, sum13}' > result2
		paste -d' '  result1 result2 >> test_result_$STANDARD_DATE
	elif [[ $line == *Insert,* ]]; then
		echo "insert,"
		echo $line |awk '{print $1, $2, $3, $4, $5, $6, $8, $9, $10, $11, $12, $13}' >> test_result_$STANDARD_DATE
       elif [[ $line == *Select,* ]]; then
	       echo "select,"
	       echo $line |awk '{print $1, $2, $3, $4, $5, $6, $8, $9, $10, $11, $12, $13}' >> test_result_$STANDARD_DATE
       elif [[ $line == *Update,* ]]; then
	       echo "update,"
	       echo $line |awk '{print $1, $2, $3, $4, $5, $6, $8, $9, $10, $11, $12, $13}' >> test_result_$STANDARD_DATE
       elif [[ $line == *Delete,* ]]; then
	       echo $line |awk '{print $1, $2, $3, $4, $5, $6, $8, $9, $10, $11, $12, $13}' >> test_result_$STANDARD_DATE
       fi
       (( count++ ))
       echo $count
    done< $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql



done
rm -f result1 result2
echo "Date, Server, Product, Revision, Testname, TestDetail, Interface, Thread, Unit, Result, Latency(%), Min(ms), Max(ms), Avg(ms), CpuUsage, MemoryUsage" > final_result
paste -d',' test_result_$STANDARD_DATE $STANDARD_HOME/work/HDB/$STANDARD_INTERFACE/$1/usage_result >> ./final_result
