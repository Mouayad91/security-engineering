#1. Muss in endlosschleife laufen
#2. Nicht strg+c erlauben zu schliessen
#3. Eingabe von user, username und tan

# if tan exists and not used, then zugriff erlaubt
# if tan exists and used, then zugriff verweigert
# if tan not exist then zugriff verweigert

trap '' 2

while :
do
    echo "Press Q to exit"
    echo "Enter username: "
    read USERNAME
    if [[ $USERNAME = "q" ]] || [[ $USERNAME = "Q" ]] 
        then break 
    fi

    echo "Enter TAN: "
    read TAN
    if [[ $TAN = "q" ]] || [[ $TAN = "Q" ]] 
        then break 
    fi

    printf "\n"

    TAN_FILE=~/TAN/$USERNAME-TAN
    TAN_USED_FILE=~/TAN/$USERNAME-TAN-USED

    if [ ! -f "$TAN_FILE" ]; then
        echo "$TAN_FILE does not exists."
        continue
    fi

    E1="false"

    while IFS= read -r line;
    do
        if [ "$line" == "$TAN" ]; then
            E1="true"
            break
        fi        
    done < $TAN_USED_FILE

    if [ $E1 == "true" ]; then
        echo "Zugriff verweigert"
        continue
    fi

    E2="false"

    while IFS= read -r line;
    do
        if [ "$line" == "$TAN" ]; then
            E2="true"
            echo $line >> $TAN_USED_FILE
            break
        fi        
    done < $TAN_FILE

    if [ $E2 == "true" ]; then
        echo "Zugriff erlaubt"
        continue
    else
        echo "Zugriff verweigert"
    fi

done