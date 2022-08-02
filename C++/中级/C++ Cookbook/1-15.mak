#default target
.PHONY: all
all: hello.exe

#rule to build hello.exe
hello.exe: hello.cpp
	cl -nologo -EHsc -GR -Zc:forScope -Zc:wchar_t \
		-Fehello hello.cpp

.PHONY: install
install:
	mkdir -p binaries
	cp -p hello.exe binaries

.PHONY: clean
clean:
	rm -f hello.exe