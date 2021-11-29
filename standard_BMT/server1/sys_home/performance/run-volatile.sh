#!/bin/sh

export PERF_HOME=`pwd`;
export PERF_SOURCE=$PERF_HOME/source;
server stop;
sed '/'VOLATILE_MAX_DB_SIZE'/d' $ALTIBASE_HOME/conf/altibase.properties > $ALTIBASE_HOME/conf/altibase.tmp;
echo "VOLATILE_MAX_DB_SIZE=60G " >> $ALTIBASE_HOME/conf/altibase.tmp;
mv $ALTIBASE_HOME/conf/altibase.tmp $ALTIBASE_HOME/conf/altibase.properties;

server start;
help(){
    echo "support [OPTION]"
    echo "	-h 	print help."
    echo "	-p	product."
    echo "	-s	scale."
    echo "	-n	test name."
    echo "	-d	test detail."
    echo "	-t	test time."
    echo "	-c	connection type."
    echo "	-i	interface."
    echo "      -k      connection count."
    exit 0
}

while getopts "p:s:n:d:t:c:i:h:k:" opt
do
    case $opt in
	p) ARG_PRODUCT=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
		echo "Test product is $ARG_PRODUCT"
                ;;

        s) ARG_SCALE=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test scale is $ARG_SCALE"
                ;;

        n) ARG_NAME=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test name is $ARG_NAME"
                ;;

        d) ARG_DETAIL=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test detail is $ARG_DETAIL"
                ;;

        t) ARG_TIME=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test time is $ARG_TIME"
                ;;

        c) ARG_CONNECTION=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test connection type is $ARG_CONNECTION"
                ;;

        i) ARG_INTERFACE=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test interface is $ARG_INTERFACE"
                ;;

        k) ARG_CONNECTION_COUNT=`echo $OPTARG | tr '[a-z]' '[A-Z]'`
                echo "Test connection count is $ARG_CONNECTION_COUNT"
                ;;

        h) help ;;

        ?) echo $OPTOPT
           help ;;
    esac
done

case $ARG_NAME in
    TPC-C)
       cd $PERF_SOURCE/$ARG_NAME
       echo $PWD
       sh run-volatile.sh -p $ARG_PRODUCT -t $ARG_TIME -i $ARG_INTERFACE -g $ARG_SCALE -k $ARG_CONNECTION_COUNT
        ;;
    TPC-H)
       cd $PERF_SOURCE/$ARG_NAME
       sh run-volatile.sh -p $ARG_PRODUCT -s $ARG_SCALE
        ;;
    COMVERSE)
        ;;
    STANDARDBMT)
       cd $PERF_SOURCE/$ARG_NAME
       echo $PWD
       sh run.sh -p $ARG_PRODUCT -i $ARG_INTERFACE -g $ARG_SCALE -s volatile
        ;;
    DBLINK)
       cd $PERF_SOURCE/$ARG_NAME
       echo $PWD
       sh run.sh -p $ARG_PRODUCT -s $ARG_SCALE
        ;;
    SIMPLEBMT)
       cd $PERF_SOURCE/$ARG_NAME
       echo $PWD
       export TESTNAME="SIMPLEBMT"
       echo $TESTNAME 
       sh run.sh -p $ARG_PRODUCT -i $ARG_INTERFACE -g $ARG_SCALE -s volatile
        ;;
    LAZYREPLICATION)
        ;;
    SCALARSUBQUERYCACHING)
        ;;
    EAGERREPLICATION)
        ;;
    QUERYRESULTSETCACHEEVENT)
        ;;
esac

#shift $(( $OPTIND - 1))
#file=$1
#echo "$file"
