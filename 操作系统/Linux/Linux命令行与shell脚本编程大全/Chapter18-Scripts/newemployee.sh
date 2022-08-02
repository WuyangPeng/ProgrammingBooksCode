#!/bin/bash
temp=$(mktemp -t record.XXXX)

function newrecord {
dialog --form "Enter new employee" 19 50 0 \
   "Last name " 1 1 "" 1 15 30 0 \
   "First name " 3 1 "" 3 15 30 0 \
   "Address " 5 1 "" 5 15 30 0 \
   "City " 7 1 "" 7 15 30 0 \
   "State " 9 1 "" 9 15 30 0 \
   "Zip " 11 1 "" 11 15 30 0 2>$temp

last=$(cat $temp | head -1)
first=$(cat $temp | head -2 | tail -1)
address=$(cat $temp | head -3 | tail -1) 
city=$(cat $temp | head -4 | tail -1)
state=$(cat $temp | head -5 | tail -1)
zip=$(cat $temp | head -6 | tail -1)
record="INSERT INTO employees (last, first, address, city, state, zip) VALUES 
('$last', '$first', '$address', '$city', '$state', '$zip');"
echo $record >> newrecords.txt
}

function listrecords {
dialog --title "New Data" --textbox data.txt 20 50
}

while [ 1 ]
do
dialog --menu "Employee Data" 20 30 5 \
   1 "Enter new employee" \
   2 "Display records" \
   3 "Exit" 2>$temp

if [ $? -eq 1 ]
then
    break
fi

selection=$(cat $temp)

case $selection in
1)
   newrecord ;;
2) 
   listrecords ;;
3)
    break ;;
*)
    dialog --msgbox "Invalid selection" 10 30
esac
done
rm -f $temp 2> /dev/null

