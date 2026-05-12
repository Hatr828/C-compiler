CC = gcc

CFLAGS = -Wall -Wextra -g -O0 -fno-omit-frame-pointer -I.
LDFLAGS = -fsanitize=address

TARGET = main

SRC = main.c \
      compiler/lexer/lexer.c \
      compiler/lexer/token.c \
	  compiler/parser/parser.c \
      compiler/parser/statement.c \
      lists/list.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)