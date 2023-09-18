#!/bin/sh


ADDR="iutclinfb1201l"
PORT=1

#if echo "" | socat STDIO TCP:&ADDR:&PORT &> /dev/null

while test "$PORT"  -ne 1024 
do
	if echo "" | socat STDIO TCP:"&ADDR":"&PORT" &> /dev/null
	then
		echo "$PORT"
	fi
	PORT=$(( $PORT + 1))
done
