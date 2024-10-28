# Dear god this Makefile is awful
TARGET := cumsay
VERSION := 0.2.0
RELEASE = n

CC = gcc
LD = gcc
CFLAGS := -I include
LDFLAGS :=

HEADER := $(shell find include -name '*.h')
SOURCE := $(shell find source -name '*.c')
OBJECT := $(patsubst source/%.c, build/%.o, $(SOURCE))

all: $(TARGET)

$(TARGET): $(OBJECT)
	$(LD) -o $@ $(OBJECT) $(LDFLAGS)

build/%.o: source/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@rm -rf build
