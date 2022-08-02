#!/bin/bash
#
# Daily_Archive - Archive designated files & directories
########################################################
#
# Gather Current Date
#
today=$(date +%y%m%d)
#
# Set Archive File Name
#
backupFile=archive$today.tar.gz
#
# Set Configuration and Destination File
#
config_file=/archive/Files_To_Backup.txt
destination=/archive/$backupFile
#
######### Main Script #########################
#
# Check Backup Config file exists
#
if [ -f $config_file ]   # Make sure the config file still exists.
then                # If it exists, do nothing but continue on.
     echo
else                # If it doesn't exist, issue error & exit script.
     echo
     echo "$config_file does not exist."
     echo "Backup not completed due to missing Configuration File"
     echo
     exit
fi
#
# Build the names of all the files to backup
#
file_no=1               # Start on Line 1 of Config File.
exec 0< $config_file    # Redirect Std Input to name of Config File
#
read file_name          # Read 1st record
#
while [ $? -eq 0 ]      # Create list of files to backup.
do
        # Make sure the file or directory exists.
     if [ -f $file_name -o -d $file_name ]
     then
          # If file exists, add its name to the list.
          file_list="$file_list $file_name"
     else
          # If file doesn't exist, issue warning
          echo
          echo "$file_name, does not exist."
          echo "Obviously, I will not include it in this archive."
          echo "It is listed on line $file_no of the config file."
          echo "Continuing to build archive list..."
          echo
     fi
#
     file_no=$[$file_no + 1]  # Increase Line/File number by one.
     read file_name           # Read next record.
done
#
#######################################
#
# Backup the files and Compress Archive
#
echo "Starting archive..."
echo
#
tar -czf $destination $file_list 2> /dev/null
#
echo "Archive completed"
echo "Resulting archive file is: $destination"
echo
#
exit
