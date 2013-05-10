CC=g++
CFLAGS=-I./include -g -fPIC

SOURCES=$(wildcard src/*.cc)
OBJECTS=$(SOURCES:.cc=.o)

TEST_SOURCES=$(wildcard test/*.cc)
TEST_OBJECTS=$(TEST_SOURCES:.cc=.o)


all: libstrmio.so.1.0.1

libstrmio.so.1.0.1: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -Wl,-soname,libstrmio.so.1 -o libstrmio.so.1.0.1 $(OBJECTS) -lc

tests: $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(TEST_OBJECTS) -lgtest

mrdemo: demo/mrdemo.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $<

mttypedbytes: demo/mttypedbytes.o $(OBJECTS)
	$(CC) $(CFLAGS) -lpthread -o $@ $(OBJECTS) $<

.PHONY: clean runtests

clean:
	rm -f libstrmio.so.1.0.1 tests mrdemo mttypedbytes
	rm -f src/*.o test/*.o

runtests: tests
	./tests

%.o: %.cc
	$(CC) $(CFLAGS) $< -c -o $@