# Nmake macros for building Windows 32-Bit apps
TARGETOS=BOTH

!include <win32.mak>


objs=rasdial.obj

all: rasdial.exe

# Update the resource if necessary

# Update the object file if necessary

.c.obj: 
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $*.c

# Update the executable file if necessary, and if so, add the resource back in.

rasdial.exe: $(objs) $(common_objs) 
    $(link) $(linkdebug) $(conlflags) -out:rasdial.exe $(objs) $(conlibsmt) rasapi32.lib


clean:
	del *.obj
	del *.exe
