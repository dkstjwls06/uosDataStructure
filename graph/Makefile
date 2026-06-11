CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -O2
LDFLAGS ?=
LDLIBS  ?=

SOURCES := $(wildcard *.c)
TARGETS := $(SOURCES:.c=)

.PHONY: all clean

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

clean:
	rm -f $(TARGETS)
