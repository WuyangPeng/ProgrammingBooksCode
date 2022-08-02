#!/bin/bash
# Using the $0 command-line parameter in messages
#
scriptname=$(basename $0)
#
echo The $scriptname ran at $(date) >> $HOME/scripttrack.log
exit
