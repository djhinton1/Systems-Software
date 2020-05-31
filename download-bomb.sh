#!/bin/bash

echo "|----------------------|"
echo "| Binary Bomb Request  |"
echo "|----------------------|"
read -p "Type your PITT username, followed by [ENTER]: " username

regexp="^([[:alpha:]]{3}[0-9]{1,3})$"

if [[ ! $username =~ $regexp ]]; then
  echo "ERROR: Wrong username: $username"
  exit;
fi

read -p "Type your Email address, followed by [ENTER]: " usermail

if [[ ! "$usermail" =~ ^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$ ]];
then
    echo "This email address is invalid: $usermail"
    exit;
fi

curl -sSL -D .header -G -q -o .bomb.tar  \
    --data-urlencode "username=$username" \
    --data-urlencode "usermail=$usermail" \
    --data-urlencode "submit=Submit" \
    "http://thoth.cs.pitt.edu:8080"

grep "text/html" .header 1>/dev/null

if [[ $? == 0 ]];
then
  echo "ERROR: Could not download the binary bomb. Please check if you typed your credentials correctly."
  exit;
fi

if [[ ! `file .bomb.tar | grep tar | wc -l` == 1 ]]; then 
  echo "ERROR: Could not download the binary bomb. Please check if you typed your credentials correctly."
  exit;
fi


filename=`cat .header | grep filename | cut -d"=" -f2 | sed 's/\"//g'`
filename=${filename%?}

echo "SUCCESS: Saving your bomb package locally as '$filename'"
echo "Good luck!"

mv .bomb.tar ./$filename

rm .header 1>/dev/null 2>/dev/null

