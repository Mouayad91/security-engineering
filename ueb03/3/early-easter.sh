for (( i = $1; i < $2; i++ ));
  do
    if ncal -e $i | grep 'March*'
    then
      echo "-"
    fi
  done