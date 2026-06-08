CC := clang
CFLAGS := -Wall -Wextra -g

SRCS := main.c scanner.c fileio.c
TARGET := dusty

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf *.dSYM
