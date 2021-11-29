#!/bin/sh
while getopts "p:i:s:c:g:" arg

do
        case $arg in
        p) STANDARD_PRODUCT=$OPTARG 
           STANDARD_PRODUCT=`echo $STANDARD_PRODUCT | tr '[a-z]' '[A-Z]'`
           if [ $STANDARD_PRODUCT == 'HDB_TRUNK' ] || [ $STANDARD_PRODUCT == 'HDB_651' ]
           then  
           PRODUCT="HDB"
           else
           PRODUCT=$STANDARD_PRODUCT
           fi
           ;;
        i) INTERFACE=$OPTARG ;;
        s) STORAGE=$OPTARG ;;
        c) MCOUNT=$OPTARG ;;
	g) MVOLUME=$OPTARG ;;
        esac
done

INTERFACE=`echo $INTERFACE | tr '[a-z]' '[A-Z]'`
STORAGE=`echo $STORAGE | tr '[a-z]' '[A-Z]'`

STANDARD_INTERFACE=$INTERFACE
export STANDARD_INTERFACE
export STANDARD_PRODUCT

cd $HOME/performance/source/STANDARDBMT/result
rm -rf *.sql
cd $HOME/performance/source/STANDARDBMT
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
