#!/bin/sh
while getopts "p:i:s:c:g:" arg

do
        case $arg in
        p) PRODUCT=$OPTARG ;;
        i) INTERFACE=$OPTARG ;;
        s) STORAGE=$OPTARG ;;
        c) MCOUNT=$OPTARG ;;
	g) MVOLUME=$OPTARG ;;
        esac
done

PRODUCT=`echo $PRODUCT | tr '[a-z]' '[A-Z]'`
INTERFACE=`echo $INTERFACE | tr '[a-z]' '[A-Z]'`
STORAGE=`echo $STORAGE | tr '[a-z]' '[A-Z]'`

if [ $# -eq 2 ]
then
    ./standard_all.sh $PRODUCT
elif [ $# -eq 8 ]
then
    if [ $MCOUNT ]
    then
    ./standard_manual.sh $PRODUCT $INTERFACE $STORAGE $MCOUNT
    else
    export MVOLUME
    ./standard_manual.sh $PRODUCT $INTERFACE $STORAGE $MVOLUME
    fi
else
    echo "Parameter count error."
fi
