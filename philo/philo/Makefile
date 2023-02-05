NAME=philosopher

OBJS= ft_atoi.o func.o init.o philo.o utils.o

all : ${NAME}


${NAME} : ${OBJS}
	cc -Wall -Werror -Wextra ${OBJS} -o $@ 

clean :
	rm -rf ${OBJS}