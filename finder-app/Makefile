CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

# Source files and target
TARGET = writer
SRCS = writer.c
OBJS = $(SRCS:.c=.o)

# Default compiler flags
CFLAGS = -Wall -g

# Default target
all: $(TARGET)

# Rule to build the final application
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean