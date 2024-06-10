# Makefile for compiling pxfind

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -O2

# Libraries
LIBS = -lgdi32

# Target executable
TARGET = pxfind

# Source files
SRCS = pxfind.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Rule to compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
