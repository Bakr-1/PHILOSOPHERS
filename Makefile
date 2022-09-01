NAME		= philo
CC			= gcc -fsanitize=address
CFLAGS		+= -g -pthread -Wall -Wextra -Werror
RM			= /bin/rm -f

INCLUDES	= -I includes
SRCS = srcs/helper2.c srcs/helper1.c srcs/helper.c srcs/philo.c srcs/main.c
OBJS = ${SRCS:.c=.o}
all: $(NAME)

$(NAME): $(OBJS)
	${CC} $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	@printf "\033[1;32mCleaning..\e[0m\n"
	rm -f $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re:			fclean all

# die after 800
t1:
	./$(NAME) 1 800 200 200

# no die
t2:
	./$(NAME) 5 800 200 200

# no die. 'x is eating' should appear 7 times.
t3:
	./$(NAME) 5 800 200 200 7

# no die.
t4:
	./$(NAME) 4 410 200 200

# die while waiting to eat. For instance 1 will die at 300 because 4 is still eating and will only release fork at 400.
t5:

	./$(NAME) 4 310 200 100
# last but not least, test with small numbers. A philo should die.
t6:
	./$(NAME) 4 119 61 61
