echo "Enter username: "
read username
echo "Enter amount: "
read amount

usernameTanFile=~/TAN/$username-TAN;
usernameTanUsedFile=~/TAN/$username-TAN-USED

mkdir ~/TAN
touch $usernameTanFile;
touch $usernameTanUsedFile;

for ((i=0; i<$amount; i++))
do
    shuf -i 100000-999999 -n1 >> $usernameTanFile
done

echo "TAN generated at $usernameTanFile"