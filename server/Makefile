CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=gnu99

# Cross compile if CROSS_COMPILE is provided
CROSS ?=
TARGET=aesdsocket
SRC=$(TARGET).c
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CROSS)$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CROSS)$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean