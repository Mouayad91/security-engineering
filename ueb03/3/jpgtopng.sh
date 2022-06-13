JPEG=$1
FILENAME="${JPEG%.*}"
djpeg -pnm $JPEG | pnmtopng > "${FILENAME}.png"