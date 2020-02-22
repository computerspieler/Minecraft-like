CPP=g++
CPPFLAGS=-c -Wall

LD=g++
LDFLAGS=-lglut -lGL

DBG=gdb

DEL=rm
DELARGS=-frdv

OBJ=src/render.o src/debug.o src/vector.o src/main.o

all:
	@echo "You need to add one of the following target :) : debug / release / clean"

clean:
	$(DEL) $(DELARGS) $(SRC)
	$(DEL) $(DELARGS) debug
	$(DEL) $(DELARGS) release

release: $(OBJ)
	$(LD) $(LDFLAGS) -O2 -o $@ $^

debug: $(OBJ)
	$(LD) $(LDFLAGS) -g -o $@ $^
	$(DBG) $@

.o: .cpp
	$(CPP) $(CPPFLAGS) -o $@ $<
