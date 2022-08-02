# Specify the target file and the install directory
OUTPUTFILE=hello
INSTALLDIR=binaries

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Tell make to rebuild hello whenever hello.cpp is modified
$(OUTPUTFILE): hello.cpp

# Install and clean targets as in Example 1-16