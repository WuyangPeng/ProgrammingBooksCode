#! /bin/csh -f
#$XConsortium: dtcm.sh /main/2 1996/10/08 09:25:12 kaleb $
setenv SHELL /bin/csh
setenv _RLD_ROOT /dev/null
setenv LD_LIBRARY_PATH /tools/packages/cde/alpha/osf1/cde_cst8/dt/lib:/tools/packages/cde/alpha/osf1/cde_cst8/x11/lib:/usr/shlib:/usr/ccs/lib:/usr/lib/cmplrs/cxx:/usr/lib/cmplrs/cc:/usr/lib:/usr/local/lib:/var/shlib
eval `/tools/packages/cde/alpha/osf1/cde_cst8/dt/bin/dtsearchpath | /usr/bin/sed -e 's^/usr/dt^/tools/packages/cde/alpha/osf1/cde_cst8/dt^g'`
exec /tools/packages/cde/alpha/osf1/cde_cst8/dt/bin/dtcm $*
