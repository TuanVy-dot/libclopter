CC = gcc
CC_FLAGS = -c -fPIC -g
LD_FLAGS = -shared -I.include/

# Directories
SRC_DIR = src
OBJECT_DIR = bin

# Collect all source files from the main src directory and subdirectories
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJECT_DIR)/%.o)

LIBNAME = libclopter.so
VERSION = 0.0.1.a
AUTHOR = ngtv

LIBFULLNAME = $(LIBNAME).$(VERSION)_$(AUTHOR)

$(LIBFULLNAME): $(OBJECTS)
	$(CC) $(LD_FLAGS) -o ./$(LIBFULLNAME) $(OBJECTS)
# Rule to compile object files

$(OBJECT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create necessary subdirectories in build
	$(CC) $(CC_FLAGS) $< -o $@

# Rule to build the final executable

# Clean up build files
.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)/*
