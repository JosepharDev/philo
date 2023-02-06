NAME=philosopher

OBJS= ft_atoi.o func.o init.o philo.o utils.o

#CFLAGS = -g3 -fsanitize=thread -Wall -Werror -Wextra
 CFLAGS = -Wall -Werror -Wextra


all : ${NAME}


${NAME} : ${OBJS}
	cc ${CFLAGS} ${OBJS} -o $@ 

clean :
	rm -rf ${OBJS}