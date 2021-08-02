

SRC					=
HDR					=	cub3dh.h
OBJ					=	${SRC:%.c=%.o}
NAME				=	philo
CFLAGS				=	-Wall -Wextra -Werror
NORM				=	norminetteV2
NORMO				=	${SRC} ${HDR}


all:				${NAME}

%.o:				%.c ${HDR}
					gcc ${CFLAGS} -c $< -o  $@

${NAME}: 			${OBJ} libmlx.dylib
					gcc ${OBJ} libmlx.dylib -o ${NAME}

clean:
					@rm -f ${OBJ}

fclean:				clean
					@rm -f ${NAME}

norm:
					@${NORM} ${NORMO}

re:					fclean ${NAME}

.PHONY:				all clean fclean re