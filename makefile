SRC		= mandelbrot.c

CC		= gcc

OBJ		= ${SRC:.c=.o}

NAME	= mandelbrot

CFLAGS	= -lm

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJ}
			${CC} -o ${NAME} ${OBJ} ${CFLAGS}

all:		${NAME}

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all