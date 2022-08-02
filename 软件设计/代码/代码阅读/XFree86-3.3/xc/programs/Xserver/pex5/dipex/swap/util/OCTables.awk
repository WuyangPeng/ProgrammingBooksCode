# $XConsortium: OCTables.awk,v 5.2 94/04/17 20:36:37 rws Exp $
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
##	awk -f OCTables.awk temp.dat <pex-include-path>/PEX.h > <output_file>
##
BEGIN { num=0; i=0; 
    print "/* Automatically generated OC table"
    print " */"
    print "/******************************************************************"
    print "Copyright 1990, 1991 by Sun Microsystems, Inc. and the X Consortium."
    print ""
    print "                        All Rights Reserved"
    print ""
    print "Permission to use, copy, modify, and distribute this software and its "
    print "documentation for any purpose and without fee is hereby granted, "
    print "provided that the above copyright notice appear in all copies and that"
    print "both that copyright notice and this permission notice appear in "
    print "supporting documentation, and that the names of Sun Microsystems "
    print "and the X Consortium not be used in advertising or publicity "
    print "pertaining to distribution of the software without specific, written "
    print "prior permission.  "
    print ""
    print "SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, "
    print "INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT "
    print "SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL "
    print "DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,"
    print "WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,"
    print "ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS"
    print "SOFTWARE."
    print ""
    print "******************************************************************/"
    print "#include \"X.h\""
    print "#include \"PEX.h\""
    print "#include \"PEXprotost.h\""
    print "#include \"PEXproto.h\""
    print "#include \"dipex.h\""
    print "#include \"pexSwap.h\"\n" }
##
## Look only for lines starting with PEXOC (in PEX.h).
## Name (minus PEXOC) is saved in array for printing at the end
## (signalled by reaching "PEXMaxOC").  This allows us to do the
## extern declarations and the table in one pass.
##
 $1 == "#define" {
    if ($2 == "PEXMaxOC") {
	print "extern ErrorCode"
	for (i=0; i<(num-1); i++) {
	    print "\tSWAP_OC_PREFIX(" str[i] ") ()," }
	print "\tSWAP_OC_PREFIX(" str[i] ") ();\n"
	print "OCFunction SWAP_OC_PREFIX(OutputCmd) [] = {"
	for (i=0; i<(num-1); i++) {
	    print "\tSWAP_OC_PREFIX(" str[i] ")," }
	print "\tSWAP_OC_PREFIX(" str[i] ")"
	print "};\n\n#undef SWAP_OC_PREFIX" }
    else if (index($2,"PEXOC") == 1) {
	str[num] = substr($2,6,(length($2)-5))
	num++ }
    }
##
## The next few lines are only for determining the name of the OC_PREFIX
## from the temporary file just made up for this purpose.
##
$1 == "STUB_NAME" {
	print "#if defined (__STDC__)"
	print "#define SWAP_OC_PREFIX(t)\t" $2 "##t"
	print "#else"
	print "#define SWAP_OC_PREFIX(t)\t" $2 "/**/t"
	print "#endif\n" }
##
##
END { }
