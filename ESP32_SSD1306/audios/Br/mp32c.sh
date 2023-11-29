#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "You must enter exactly 2 command line arguments"
    exit
fi

ffmpeg -i $1 -f u8 -acodec pcm_u8 -ar 8000 -ac 1 output.raw
xxd -i -a output.raw >> $2
rm output.raw