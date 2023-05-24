#!/bin/sh

echo "Converting files to 8bit unsigned PCM WAV"

ORIG="cancion2.mp3"*
echo "Original files are located at $ORIG"

for file in $ORIG
do
	FILE=`basename $file`
	if [ ! -f $FILE.wav ]; then
		echo "*** Processing $FILE"
		ffmpeg -n -i $file -ar 11000 -acodec pcm_u8 -ac 1 $FILE.wav
	else	
		echo "*** $FILE exists"
	fi
done