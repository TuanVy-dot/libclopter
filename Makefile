CC = gcc
CC_FLAGS = -c -fPIC -I./include/ -I./lib/ -g -Wall -Wextra -Wpedantic
LD_FLAGS = -shared -I./include/ -I./lib/

SRC_DIR = src
HDR_DIR = include
OBJECT_DIR = bin
DB_OBJECT_DIR = bin_db

HEADERS = $(wildcard $(HDR_DIR)/*.h $(wildcard $(HDR_DIR)/**/*.h))
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJECT_DIR)/%.o)
DB_OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(DB_OBJECT_DIR)/%.o)

LIBNAME = libclopter.so
VERSION =
AUTHOR =

LIBFULLNAME = $(LIBNAME)$(VERSION)$(AUTHOR)

lib: $(OBJECTS)
	$(CC) $(LD_FLAGS) -o $(OBJECT_DIR)/$(LIBFULLNAME) $(OBJECTS)

libdb: $(DB_OBJECTS)
	$(CC) $(LD_FLAGS) -g -L./lib -llogger -o $(DB_OBJECT_DIR)/$(LIBFULLNAME) $(DB_OBJECTS)

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) $< -o $@

$(DB_OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -DLOG $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)/* $(DB_OBJECT_DIR)/*
