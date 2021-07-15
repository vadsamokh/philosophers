.PHONY:	re all fclean

NAME =	philo

SRCS =	./main.c \
		./life_actions.c \
		./philos.c \
		./utils.c

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

${NAME}: ${SRCS}
		${CC} ${SRCS} -o ${NAME} ${CFLAGS}

fclean:
		rm -f ${NAME}

re:		fclean all
