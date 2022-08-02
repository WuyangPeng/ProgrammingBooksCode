#!/bin/bash
#
# Audit_System.sh - Audit system files and accounts
####################################################
#
### Intialize variables #######################
#
runAccountAudit="false"
runPermAudit="false"
#
reportDir="/home/christine/scripts/AuditReports"
#
### Get options (if provided) #################
#
while getopts :Ap opt
do
     case "$opt" in
          A) runAccountAudit="true" ;;
          p) runPermAudit="true" ;;
          *) echo "Not a valid option."
             echo "Valid options are: -A, -p, or -Ap" 
             exit
          ;;
     esac
done
#
### Determine if no options ##################
#
if [ $OPTIND -eq 1 ]
then
     # No options were provided; set all to "true" 
     runAccountAudit="true"
     runPermAudit="true"
fi
#
### Run selected audits #######################
#
## Account Audit ##################
#
if [ $runAccountAudit = "true" ]
then
    echo
    echo "****** Account Audit *****"
    echo
#
# Determine current false/nologin shell count
#
    echo "Number of current false/nologin shells: "
#
    reportDate="$(date +%F%s)"
    accountReport=$reportDir/AccountAudit$reportDate.rpt
#
    # Create current report
    cat /etc/passwd | cut -d: -f7 |
    grep -E "(nologin|false)" | wc -l |
    tee $accountReport
#
    # Change report's attributes:
    sudo chattr +i  $accountReport
#
# Show past false/nologin shell count
#
    prevReport="$(ls -1t $reportDir/AccountAudit*.rpt | sed -n '2p')"
    if [ -z $prevReport ]
    then
         echo
         echo "No previous false/nologin report exists to compare."
    else
         echo
         echo "Previous report's false/nologin shells: "
         cat $prevReport
    fi
fi
#
## Permissions Audit ##############
#
if [ $runPermAudit = "true" ]
then
    echo
    echo "****** SUID/SGID Audit *****"
    echo
    reportDate="$(date +%F%s)"
    permReport=$reportDir/PermissionAudit$reportDate.rpt
#
    # Create current report
    echo "Creating report. This may take a while..."
    sudo find / -perm /6000 >$permReport 2>/dev/null  
#
    # Change report's attributes:
    sudo chattr +i  $permReport
#
# Compare to last permission report
#
    #
    prevReport="$(ls -1t $reportDir/PermissionAudit*.rpt | sed -n '2p')"
    #
    if [ -z $prevReport ]
    then
         echo
         echo "No previous permission report exists to compare."
    else
         echo
         echo "Differences between this report and the last: "
         #
         differences=$(diff $permReport $prevReport)
         #
         if [ -z "$differences" ]
         then
             echo "No differences exist."
         else
             echo $differences
         fi
    fi
fi
#
exit
