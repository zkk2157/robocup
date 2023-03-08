#!/bin/bash
#
# RoboCup 2012 sample start script for 3D soccer simulation
#
#export LD_LIBRARY_PATH==$LD_LIBRARY_PATH:citlib/

AGENT_BINARY="CIT3D_BINARY"
BINARY_DIR="./"
NUM_PLAYERS=11
$IPAddress

if [ -z $1 ] ; then
{
	echo "please set host"
	IPAddress=127.0.0.1
}
else
{
	IPAddress=$1
}
fi


for ((i=1;i<=$NUM_PLAYERS;i++)); do
   echo "Running $AGENT_BINARY agent No. $i"
  "$BINARY_DIR$AGENT_BINARY" --host=$IPAddress --Unum=$i --team='CHEN'  > ./log/chenstdout$i.out 2> ./log/chenstderr$i.err &
sleep 1
done

