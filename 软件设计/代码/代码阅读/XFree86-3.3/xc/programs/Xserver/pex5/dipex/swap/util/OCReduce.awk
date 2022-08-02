## 
# $XConsortium: OCReduce.awk,v 5.2 94/04/17 20:36:36 rws Exp $
## 
###########################################################################
## Copyright 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.
## 
##                         All Rights Reserved
## 
## Permission to use, copy, modify, and distribute this software and its 
## documentation for any purpose and without fee is hereby granted, 
## provided that the above copyright notice appear in all copies and that
## both that copyright notice and this permission notice appear in 
## supporting documentation, and that the names of Sun Microsystems
## and the X Consortium not be used in advertising or publicity 
## pertaining to distribution of the software without specific, written 
## prior permission.  
## 
## SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
## INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
## SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
## DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
## WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
## ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
## SOFTWARE.
## 
###########################################################################
## Usage:
##	rm -f temp.dat
##	echo "STUB_NAME " <stub_name> | cat > temp.dat
##	awk -f OCTables.awk temp.dat <pex-include-path>/PEX.h | awk -f OCReduce.awk | sed -f OCReduce.sed > <output_file>
##
BEGIN { }
 {
  if ($1 ~ /ColourIndex/) {
    if ($1 ~ /MarkerColourIndex/ ) { print $0 }
    else if ($2 !~ /\(\)/) { 
	lh = index($1,"(")
	rh = index($1,")")
	name = substr($1,(lh+1),(rh-lh-1))
	if ($0 ~ /,/) {
	    print "\tSwapPEXMarkerColourIndex,\t/* " name " */" }
	else {
	    print "\tSwapPEXMarkerColourIndex\t/* " name " */" } } }
  else if ($1 ~ /Index\)/) {
    if ($1 ~ /MarkerBundleIndex/ ) { print $0 }
    else if ($2 !~ /\(\)/) { 
	lh = index($1,"(")
	rh = index($1,")")
	name = substr($1,(lh+1),(rh-lh-1))
	if ($0 ~ /,/) {
	    print "\tSwapPEXMarkerBundleIndex,\t/* " name " */" }
	else {
	    print "\tSwapPEXMarkerBundleIndex\t/* " name " */" } } }
  else if ($1 ~ /Colour/) {
    if ($1 ~ /MarkerColour/ ) { print $0 }
    else if ($2 !~ /\(\)/) { 
	lh = index($1,"(")
	rh = index($1,")")
	name = substr($1,(lh+1),(rh-lh-1))
	if ($0 ~ /,/) {
	    print "\tSWAP_OC_PREFIX(MarkerColour),\t/* " name " */" }
	else {
	    print "\tSWAP_OC_PREFIX(MarkerColour)\t/* " name " */" } } }
  else if ( $1 ~ /Bf/) {
    if ($2 !~ /\(\)/) { 
	lh = index($1,"Bf")
	rh = index($1,")")
	name = substr($1,(lh+2),(rh-lh-2))
	if (($1 ~ /Colour/) && ($1 !~ /Index/) || ($1 ~ /SurfaceReflAttr/)) {
	    if ($0 ~ /,/) {
		print "\tSWAP_OC_PREFIX(" name "),\t/* Bf" name " */" }
	    else {
		print "\tSWAP_OC_PREFIX(" name ")\t/* Bf" name " */" } }
	else {
	    if ($0 ~ /,/) {
		print "\tSwapPEX" name ",\t/* Bf" name " */" }
	    else {
		print "\tSwapPEX" name "\t/* Bf" name " */" } } } }
  else if ($1 ~ /Atext/) {
    if ($1 ~ /Style/) { print $0 }
    else if ($2 !~ /\(\)/) {
	if (($1 ~ /AtextHeight/) || ($1 ~ /AtextUpVector/)) {
	    lh = index($1,"(")
	    rh = index($1,")")
	    name = substr($1,(lh+6),(rh-lh-6))
	    if ($0 ~ /,/) {
		print "\tSwapPEXChar" name ",\t/* Atext" name " */" }
	    else {
		print "\tSwapPEXChar" name "\t/* Atext" name " */" } }
	else {
	    lh = index($1,"(")
	    rh = index($1,")")
	    name = substr($1,(lh+3),(rh-lh-3))
	    if ($0 ~ /,/) {
		print "\tSwapPEXT" name ",\t/* At" name " */" }
	    else {
		print "\tSwapPEXT" name "\t/* At" name " */" } } } }
  else if ($1 ~ /RemoveFromNameSet/) {
    if ($2 !~ /\(\)/) { 
	lh = index($1,"(")
	rh = index($1,")")
	name = substr($1,(lh+1),(rh-lh-1))
	if ($0 ~ /,/) {
	    print "\tSWAP_OC_PREFIX(AddToNameSet),\t/* " name " */" }
	else {
	    print "\tSWAP_OC_PREFIX(AddToNameSet0\t/* " name " */" } } }
  else if ($1 ~ /SurfaceEdgeWidth/) {
    if ($2 !~ /\(\)/) {
	lh = index($1,"(")
	rh = index($1,")")
	name = substr($1,(lh+1),(rh-lh-1))
	if ($0 ~ /,/) {
	    print "\tSwapPEXLineWidth,\t/* " name " */" }
	else {
	    print "\tSwapPEXLineWidth\t/* " name " */" } } }
  else if ($1 ~ /TCApproximation/) {
    if ($2 !~ /\(\)/) {
	lh = index($1,"(")
	rh = index($1,")")
	name = substr($1,(lh+1),(rh-lh-1))
	if ($0 ~ /,/) {
	    print "\tSwapPEXCurveApproximation,\t/* " name " */" }
	else {
	    print "\tSwapPEXCurveApproximation\t/* " name " */" } } }
  else if ($1 ~ /\(All\)/) {
    lh = index($0,"SWAP_OC_PREFIX(") - 1
    rh = index($0,")") + 1
    print substr($0,1,lh) "SwapPEXOCUnused" substr($0,rh,(length($0)+1-rh)) }
  else print $0
 }
END { }
