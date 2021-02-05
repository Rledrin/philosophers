NAME        = philo_one

CC          = gcc

RM          = rm -rf

OBJS_DIR    = ./objects

SRCS_DIR    = ./srcs

CFLAGS      = -Wall -Wextra -Werror -Iincludes
# CFLAGS      = -Wall -Wextra -Werror -Iincludes -fsanitize=thread -g3 -O2
# CFLAGS      = -Wall -Wextra -Werror -Iincludes -fsanitize=leak -g3 -O2

LIBS		= -lpthread

SRCS		= main.c \
			  utils.c \
			  errors.c \
			  running_philo.c \
			  init_philo.c \


OBJS        = ${SRCS:%.c=${OBJS_DIR}/%.o}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c

			@mkdir -p ${@D}

			${CC} ${CFLAGS} -c $< -o $@



${NAME}:    ${OBJS}

			${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBS}

all:        ${NAME}

clean:
			@${RM} ${OBJS} ${OBJS_DIR}

			@printf "\033[0;35mPROJECT\033[0;0m:      \033[0;32mCleaned\033[0;0m\n"

fclean:     clean

			@${RM} ${NAME}

re:         fclean all

silent:

            @:

.PHONY:     all clean fclean re bonus
