#!/bin/bash
# Change the shebang used for a directory of scripts
#
################## Function Declarations ##########################
#
function errorOrExit {
	echo
	echo $message1
	echo $message2
	echo "Exiting script..."
	exit
}
#
function modifyScripts {
	echo
	read -p "Directory name in which to store new scripts? " newScriptDir
	#
	echo "Modifying the scripts started at $(date +%N) nanoseconds"
	#
	count=0
	for filename in $(grep -l "/bin/sh" $scriptDir/*.sh)
	do
		newFilename=$(basename $filename)
		cat $filename | 
		sed '1c\#!/bin/bash' > $newScriptDir/$newFilename
		count=$[$count + 1] 
	done
	echo "$count modifications completed at $(date +%N) nanoseconds"
}
#
################# Check for Script Directory ######################
if [ -z $1 ]
then 
	message1="The name of the directory containing scripts to check"
	message2="is missing. Please provide the name as a parameter."
        errorOrExit
else
	scriptDir=$1
fi 
#
################ Create Shebang Report ############################
#
sed -sn '1F; 
1s!/bin/sh!/bin/bash!' $scriptDir/*.sh | 
gawk 'BEGIN {print ""
print "The following scripts have /bin/sh as their shebang:"
print "==================================================="}
{print $0}
END {print ""
print "End of Report"}'
#
################## Change Scripts? #################################
#
#
echo
read -p "Do you wish to modify these scripts' shebang? (Y/n)? " answer
#
case $answer in
Y | y)
	modifyScripts
	;;
N | n)
	message1="No scripts will be modified."
	message2="Run this script later to modify, if desired."
	errorOrExit
	;;
*)
	message1="Did not answer Y or n."
	message2="No scripts will be modified."
	errorOrExit
	;;
esac
