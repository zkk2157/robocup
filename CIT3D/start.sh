#!/bin/bash
#
# Robocup 2015 sample start script for 3D soccer simulation
#
export LD_LIBRARY_PATH==$LD_LIBRARY_PATH:citlib/

AGENT_BINARY="CIT3D_binary"
BINARY_DIR="./"
NUM_PLAYERS=11
$IPAddress

if [ -z $1 ] ; then
{
       echo "please set host"
	IPAddress=192.168.1.12
}
else
{
	IPAddress=$1
}
fi

killall -9 "$AGENT_BINARY" &> /dev/null

for ((i=1;i<=$NUM_PLAYERS;i++)); do
   echo "Running $AGENT_BINARY agent No. $i"
  "$BINARY_DIR$AGENT_BINARY" --host=$IPAddress --Unum=$i --team='CIT3D'  > /dev/null 2> /dev/null &
sleep 1
done

