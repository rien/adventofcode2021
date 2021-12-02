CC = musl-gcc
CFLAGS = -s -march=native -Ofast -std=c99 -Wconversion -Werror -Wall -Wpedantic -Wextra -static

DAYS := $(shell find inputs/ -type f -name 'input*' | sed 's/.*\([0-9][0-9]\).*/\1/')
LIBS := $(shell find lib/ -type f -name '*.c')

INPUT ?= input

define day
$(shell echo $< | sed 's_.*day\(..\).*_\1_')
endef

define day_part
$(shell echo $< | sed 's_.*day\(....\).*_\1_')
endef

out/%: days/%.c $(LIBS)
	$(CC) $(CFLAGS) $< -o $@

run_%: out/day%
	$< < inputs/$(INPUT)$(call day,$<).txt

test_%: out/day%
	diff -w <($< < inputs/$(INPUT)$(call day,$<).txt) outputs/$(call day_part,$<).out

.PHONY: clean all test format

format:
	clang-format -i days/*.c lib/*.c

test: $(foreach d,$(DAYS),test_$(d)_1 test_$(d)_2)

all: $(foreach d,$(DAYS),out/day$(d)_1 out/day$(d)_2)

clean:
	rm -rf out/*
