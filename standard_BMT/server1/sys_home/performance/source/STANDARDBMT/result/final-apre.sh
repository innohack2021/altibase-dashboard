if [ "$TESTNAME" ];
then
    TESTCASE="$TESTNAME"
else
#    TESTCASE="HDB-APRE HDB-JDBC HDB-SQLCLI"
    TESTCASE="XDB-APRE XDB-SQLCLI"
fi

rm -f test_result

for TESTCASE in $TESTCASE
do

line="16 18 20 22 24 26 28 30 32 35 38 41"
sed -n '1,15p' $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{print $1, $2, $3, $4, $6, $7}' >> test_result

for i in $line
do
    if [ $i -ge 32 ];
    then
    	let j=$i+2
    else
        let j=$i+1
    fi

    sed -n "$i"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{print $1, $2, $3, $4, $5}' > result1
    sed -n "$i","$j"p $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{sum+=$7 } END {printf "%.6f\n", sum}' > result2
    paste -d' '  result1 result2 >> test_result
done

sed -n '44,48p' $STANDARD_HOST'_'$TESTCASE'_'$STANDARD_DATE.sql | awk '{print $1, $2, $3, $4, $6, $7}' >> test_result

done
rm -f result1 result2
