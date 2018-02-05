CC=g++
CXXFLAGS+= -Wall -Wpedantic -fPIC -Os -pipe
LDFLAGS+= -lX11 -s

testxhotkeys: testxhotkeys.o xhotkeys.o xkeygrab.o

.PHONY: clean
clean:
	rm -rf *.o
