NAME = philo
CC = CC
RM = rm -rf
OBJS = ft_atoi.o func.o init.o philo.o utils.o action.o

# CFLAGS = -g3 -fsanitize=thread -Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@ 

clean :
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re: clean all