NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
SRC = action.c ft_atoi.c func.c init.c philo.c utils.c

OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	${RM} ${OBJ} ${OBJB}

fclean : clean
	${RM} ${NAME}

re : fclean all