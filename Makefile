SRCS=$(wildcard src/*.c)
DEPS=$(patsubst src/%,bin/deps/%.d,$(SRCS))
OBJS=$(patsubst src/%,bin/objs/%.o,$(SRCS))

CC=gcc
LD=gcc
CCFLAGS=-Wall -Wextra -Isrc -c -std=c89
#-std=c89
LDFLAGS=-lGL -lGLU -lglut -lm

all: debug

clean:
	rm -rf bin

-include $(DEPS)

debug: bin/debug
release: bin/release

bin/release: CCFLAGS := $(CCFLAGS) -O2
bin/release: $(OBJS)
	$(LD) -o $@ $^ -O2 $(LDFLAGS)

bin/debug: CCFLAGS := $(CCFLAGS) -g -ggdb
bin/debug: $(OBJS)
	$(LD) -o $@ $^ -g -ggdb $(LDFLAGS)

bin/objs/%.c.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<

bin/deps/%.c.d: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst bin/deps/%,bin/objs/%,$@)

