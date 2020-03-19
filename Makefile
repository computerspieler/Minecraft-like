CPP=g++
CPPFLAGS=-c -Wall

LD=g++
LDFLAGS=-lglut -lGL

DBG=gdb

DEL=rm
DELARGS=-frdv

OBJ=src/main.o src/render/render.o src/debug.o src/math/vector.o \
	src/render/camera.o src/render/texture.o src/render/shapes.o \
	src/render/bmp_reader.o

all:
	@echo "You need to add one of the following target :) : debug / release / clean"

clean:
	$(DEL) $(DELARGS) $(OBJ)
	$(DEL) $(DELARGS) debug
	$(DEL) $(DELARGS) release

release: $(OBJ)
	$(LD) $(LDFLAGS) -O2 -o $@ $^

debug: $(OBJ)
	$(LD) $(LDFLAGS) -g -o $@ $^
	$(DBG) $@

.o: .cpp
	$(CPP) $(CPPFLAGS) -o $@ $<
