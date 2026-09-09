NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SOURCES =	main.c \
			check_functions.c \
			init_functions.c \
			tools.c \
			threads.c \
			actions.c \
			monitor.c \
			forks.c \
			state.c \
			print_functions.c \
			simulation.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re