PROGRAM_NAME		=	philo

HDR_PATH			=	includ
SRC_PATH			=	src

SRC					=	main.c		init_mutex.c	init_philo.c \
						sumulation.c	time.c		write_func.c
HDR					=	philo.h

OBJ					=	${SRC:${SRC_PATH}/%.c=%.o}

CFLAGS				=	-Wall -Wextra -Werror

LIB_INC				=	-lpthread
LIB_PATH_INC		=	-I${HDR_PATH}

NORM				=	norminetteV3
NORMO				=	${SRC} ${HDR}



all:				${PROGRAM_NAME}

${PROGRAM_NAME}: 	${OBJ}
					gcc ${LIB_PATH_INC} ${OBJ} ${LIB_INC} -o ${NAME}

%.o:				%.c ${HDR}
					gcc ${CFLAGS} -c $< -o  ./obj/$@

clean:
					@rm -f ./obj/${OBJ}

fclean:				clean
					@rm -f ${NAME}

norm:
					@${NORM} ${NORMO}

re:					fclean ${NAME}

.PHONY:				all clean fclean re