if [ $# -lt 1 ]
 then
  echo "Error: No arguments were passed"
  exit 1
fi

HASHED_PASS="$1"
PATH_DICT="/usr/share/dict/words"

if [ ! -r "$PATH_DICT" ]
 then
  echo "File not found: $PATH_DICT"
  exit 2
fi

SALT="$(echo $HASHED_PASS | rev | cut -c 1-7)"

for word in $(cat $PATH_DICT);
  do
	CURRENT_PASS="$(openssl passwd -1 -salt "$SALT" "$word")"
	if [ "$CURRENT_PASS" = "$HASHED_PASS" ];
    then
      echo "MATCHED PASSWORD '$HASHED_PASS' FOR WORD: '$word'"
      exit 0
    fi
  done
  
echo "NO MATCH FOR: '$HASHED_PASS'"
exit 0
