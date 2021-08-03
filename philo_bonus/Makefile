PROGRAM_NAME		=	philo_bonus

HDR_PATH			=	includ
SRC_PATH			=	src

SRC					=	src/main.c		src/init_sem.c	src/init_philo.c \
						src/simulation.c	src/time.c		src/write_func.c \
						src/libft_func.c	src/philo_process.c
HDR					=	includ/philo_bonus.h

OBJ					=	${SRC:%.c=%.o}

CFLAGS				=	-Wall -Wextra -Werror

LIB_INC				=	-lpthread
LIB_PATH_INC		=	-I${HDR_PATH}

NORM				=	norminetteV3
NORMO				=	${SRC} ${HDR}



all:				${PROGRAM_NAME}

${PROGRAM_NAME}: 	${OBJ}
					gcc ${LIB_PATH_INC} ${OBJ} ${LIB_INC} -o ${PROGRAM_NAME}

%.o:				%.c ${HDR}
					gcc ${CFLAGS} ${LIB_PATH_INC} -c $< -o  $@

clean:
					@rm -f ${OBJ}

fclean:				clean
					@rm -f ${PROGRAM_NAME}

norm:
					@${NORM} ${NORMO}

re:					fclean ${PROGRAM_NAME}

.PHONY:				all clean fclean re