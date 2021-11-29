#!/bin/bash

echo "start prog" 
rm -f ./top.log
echo "delete top.log"
while [ : ];
do
./cpu.sh >> top.log
sleep 1 ;
done 
