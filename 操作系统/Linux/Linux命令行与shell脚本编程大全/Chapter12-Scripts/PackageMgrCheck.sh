#!/bin/bash
# Checks system for popular package managers 
#
#################### User Introduction ######################
echo "########################################################"
echo 
echo "     This script checks your Linux system for popular"
echo "package managers and application containers, lists" 
echo "what's available, and makes an educated guess on your"
echo "distribution's base distro (Red Hat or Debian)."
echo
echo "#######################################################"
#
##################### Red Hat Checks #######################
#
echo 
echo "Checking for Red Hat-based package managers &" 
echo "application containers..."
#####
if (which rpm &> /dev/null)
then
     item_rpm=1
     echo "You have the basic rpm utility."
#
else
     item_rpm=0
#
fi
####
if (which dnf &> /dev/null)
then
     item_dnfyum=1
     echo "You have the dnf package manager."
#
elif (which yum &> /dev/null)
then
     item_dnfyum=1
     echo "You have the yum package manager."
else
     item_dnfyum=0
#
fi
####
if (which flatpak &> /dev/null)
then
     item_flatpak=1
     echo "You have the flatpak application container."
#
else
     item_flatpak=0
#
fi
####
redhatscore=$[$item_rpm + $item_dnfyum + $item_flatpak]
#
##################### Debian Checks #######################
#
echo 
echo "Checking for Debian-based package managers &" 
echo "application containers..."
#####
if (which dpkg &> /dev/null)
then
     item_dpkg=1
     echo "You have the basic dpkg utility."
#
else
     item_dpkg=0
#
fi
####
if (which apt &> /dev/null)
then
     item_aptaptget=1
     echo "You have the apt package manager."
#
elif (which apt-get &> /dev/null)
then
     item_aptaptget=1
     echo "You have the apt-get/apt-cache package manager."
#
else
     item_aptaptget=0
fi
####
if (which snap &> /dev/null)
then
     item_snap=1
     echo "You have the snap application container."
#
else
     item_snap=0
#
fi
####
#
debianscore=$[$item_dpkg + $item_aptaptget + $item_snap]
#
#
##################### Determine Distro #######################
#
echo
if [ $debianscore -gt $redhatscore ]
then
   echo "Most likely your Linux distribution is Debian-based."
   #
elif [ $redhatscore -gt $debianscore ]
then
   echo "Most likely your Linux distribution is Red Hat-based."
else
   echo "Unable to determine Linux distribution base."
fi
#
echo
#
#############################################################
#
exit 
