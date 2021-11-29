#!/bin/bash

WHOAMI=`whoami`
pro_id=`ps -ef | grep /bin/altibase | grep $WHOAMI |grep -v grep | awk '{print $2}'`
UNIX95= ps -p $pro_id -o pid,pcpu,sz,ruser,args | grep altibase 
