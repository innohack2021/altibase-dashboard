#!/bin/sh
while getopts "p:i:s:c:r:g:" arg

do
        case $arg in
        p) STANDARD_PRODUCT=$OPTARG 
           STANDARD_PRODUCT=`echo $STANDARD_PRODUCT | tr '[a-z]' '[A-Z]'`
           if [ STANDARD_PRODUCT='HDB_TRUNK' ] || [ STANDARD_PRODUCT='HDB_651' ]
           then  
           PRODUCT="HDB"
           else
           echo "Product name error."
           fi
           ;;
        i) INTERFACE=$OPTARG ;;
        s) STORAGE=$OPTARG ;;
        r) MCOUNT=$OPTARG ;;
        c) MCOUNT=$OPTARG ;;
	g) MVOLUME=$OPTARG ;;
        esac
done

INTERFACE=`echo $INTERFACE | tr '[a-z]' '[A-Z]'`
STORAGE=`echo $STORAGE | tr '[a-z]' '[A-Z]'`

STANDARD_INTERFACE=$INTERFACE
export STANDARD_INTERFACE
export STANDARD_PRODUCT

if [ $# -eq 2 ]
then
    ./standard_all.sh $PRODUCT
elif [ $# -eq 8 ]
then
    if [ $MCOUNT ]
    then
     export MCOUNT
    bash ./standard_manual_samesize.sh $PRODUCT $INTERFACE $STORAGE $MCOUNT
    else
    export MVOLUME
    bash ./standard_manual_samesize.sh $PRODUCT $INTERFACE $STORAGE $MVOLUME
    fi
else
    echo "Parameter count error."
fi
