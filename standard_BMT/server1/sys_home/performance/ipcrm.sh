#!/bin/sh
SHMID=`ipcs -m | grep $USER | cut -d " " -f2`
SEMID=`ipcs -s | grep $USER | cut -d " " -f2`
MSQID=`ipcs -q | grep $USER | cut -d " " -f2`

for shm in $SHMID
do
        ipcrm -m $shm
done

for sem in $SEMID
do
        ipcrm -s $sem
done

for msq in $MSQID
do
        ipcrm -q $msq
done
