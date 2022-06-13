WAVFILE=$1
FILENAME="${WAVFILE%.*}"
ffmpeg -i $WAVFILE -acodec mp3 "${FILENAME}.mp3"