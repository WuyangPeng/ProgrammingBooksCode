# Specify the source files, target files, the build directories,
# and the install directory
SOURCES = hellobeatles.cpp
OUTPUTFILE = hellobeatles
LIBJOHNPAUL = libjohnpaul.a
LIBGEORGERINGO = libgeorgeringo.so
JOHNPAULDIR = ../johnpaul
GEORGERINGODIR = ../georgeringo
INSTALLDIR = ../binaries

#
# Add the parent directory as an include path
#
CPPFLAGS	+= -I..

#
# Default target
#
.PHONY: all
all: $(HELLOBEATLES)

#
# Target to build the executable.
#
$(OUTPUTFILE): $(subst .cpp,.o,$(SOURCES)) \
		$(JOHNPAULDIR)/$(LIBJOHNPAUL) \
		$(GEORGERINGODIR)/$(LIBGEORGERINGO)
	$(CXX) $(LDFLAGS) -o $@ $^

.PHONY: install
install:
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(OUTPUTFILE)

# Generate dependencies of .ccp files on .hpp files
include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$