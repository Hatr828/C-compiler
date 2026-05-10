CC = gcc

CFLAGS = -Wall -Wextra -g -Icompiler -ILists
LDFLAGS = -fsanitize=address

TARGET = main

SRC = main.c \
      compiler/lexer.c \
      compiler/token.c \
      lists/token_list.c

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