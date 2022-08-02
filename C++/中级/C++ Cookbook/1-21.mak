# Specify extensions of files to delete when cleaning
CLEANEXTS = obj lib

# Specify the target file and the install directory
OUTPUTFILE = libjohnpaul.lib
INSTALLDIR = ../binaries

# Pattern rule to build an object file from a .cpp file
%.obj: %.cpp
	"$(MSVCDIR)/bin/cl" -c -nologo -EHsc -GR -Zc:forScope -Zc:wchar_t \
		$(CXXFLAGS) $(CPPFLAGS) -Fo"$@" $<

# Default target
.PHONY: all
all: $(OUTPUTFILE)

# Build libjohnpaul.lib from john. obj, paul. obj, and johnpaul. obj
$(OUTPUTFILE): john.obj paul.obj johnpaul.obj
	"$(MSVCDIR)/bin/link" -lib -nologo -out:"$@" $^

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean
clean:
	for file in $(CLEANEXTS); do rm -f *.$$file; done

# Indicate dependency of .cpp files on .hpp files
john.obj: john.hpp
paul.obj: paul.hpp
johnpaul. obj: john.hpp paul.hpp johnpaul.hpp