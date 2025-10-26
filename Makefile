TARGET = main # name
CC = gcc
CFLAGS = -Wall -Wextra -Iincludes -g
SRCS = src/main.c src/choiceMaker.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
