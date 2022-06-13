PATH_DICT="/Users/zmohamed/GIT/PIB-SE/ueb04/3/passwords.txt"

if [ ! -r "$PATH_DICT" ]
 then
  echo "File not found: $PATH_DICT"
  exit 2
fi


while IFS= read -r line;
do
  USER="$(cut -d' ' -f1 <<< "$line")"
  PASSWORD="$(cut -d' ' -f2 <<< "$line")"
  echo "CRACKER EXECUTED FOR USER $USER"
  sh cracker.sh $PASSWORD
done < "$PATH_DICT"