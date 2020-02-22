CPP=g++
CPPFLAGS=-c -Wall

LD=g++
LDFLAGS=-lglut -lGL

DBG=gdb

DEL=rm
DELARGS=-frdv

SRC=src/main.o src/render.o

all:
	@echo "You need to add one of the following target :) : debug / release / clean"

clean:
	$(DEL) $(DELARGS) $(SRC)
	$(DEL) $(DELARGS) debug
	$(DEL) $(DELARGS) release

release: $(SRC)
	$(LD) $(LDFLAGS) -O2 -o $@ $^

debug: $(SRC)
	$(LD) $(LDFLAGS) -g -o $@ $^
	$(DBG) $@

.o: .c
	$(CPP) $(CPPFLAGS) -o $@ $<
