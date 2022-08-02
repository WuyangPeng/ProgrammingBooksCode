#!/bin/sh

# $XConsortium: confvga2.sh /main/2 1996/02/21 17:59:48 kaleb $
# $XFree86: xc/programs/Xserver/hw/xfree86/vga2/confvga2.sh,v 3.2 1996/12/23 06:54:11 dawes Exp $
#
# This script generates vga2Conf.c
#
# usage: configvga.sh driver1 driver2 ...
#

VGACONF=./vga2Conf.c

cat > $VGACONF <<EOF
/*
 * This file is generated automatically -- DO NOT EDIT
 */

#include "xf86.h"
#include "vga.h"

extern vgaVideoChipRec
EOF
Args="`echo $* | tr '[a-z]' '[A-Z]'`"
set - $Args
while [ $# -gt 1 ]; do
  echo "        $1," >> $VGACONF
  shift
done
echo "        $1;" >> $VGACONF
cat >> $VGACONF <<EOF

vgaVideoChipPtr vgaDrivers[] =
{
EOF
for i in $Args; do
  echo "        &$i," >> $VGACONF
done
echo "        NULL" >> $VGACONF
echo "};" >> $VGACONF
