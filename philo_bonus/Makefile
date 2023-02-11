NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
SRC = action.c check.c create_philo.c ft_atoi.c main.c utils.c

OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean :
	${RM} ${OBJ} ${OBJB}

fclean : clean
	${RM} ${NAME}

re : fclean all