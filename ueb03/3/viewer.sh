OUTPUT=$(file $1)

if   [[ "$OUTPUT" == *"PDF"* ]];
then
  xpdf $1

elif [[ "$OUTPUT" == *"OpenDocument Text"* ]]
then
 open $1

elif [[ "$OUTPUT" == *"image"* ]]
then
  open $1

elif [[ "$OUTPUT" == *"txt"* ]]; 
then
  less $1

fi

