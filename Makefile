NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
HEADER = included/minishell.h
RM = rm -rf 

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

SRCS = minishell.c \
	   libft/ft_strcmp.c \
	   libft/ft_split.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_strtrim.c \
	   libft/ft_strlen.c \
	   libft/ft_strdup.c \
	   libft/ft_substr.c \
	   memory/alocate_error.c \
	   parser/check_syntax.c \
	   parser/check_tokens.c \
	   parser/start_parsing.c \
	   parser/linked_list.c \
	   parser/parsing.c \
	   parser/infix_postfix.c\
	   parser/building_tree.c\
	   env/copy_env.c \
	   env/linked_env.c \
	   execution/execution.c \
	   execution/exec_cmd.c \
	   memory/free_memory.c \
	   builtins/unset.c \
	   builtins/pwd.c \
	   builtins/exit.c \
	   builtins/env.c \
	   builtins/echo.c \
	   libft/ft_atoi.c \
	   expander/expand.c \
	   libft/ft_itoa.c \
	   libft/ft_strjoin.c \
	   expander/expand_herdoc.c \
	   expander/expand_file.c \
	   builtins/export.c \
	   libft/ft_isalphnum.c \
	   libft/ft_atoll.c \
	   builtins/cd.c \
	   herdoc/handle_herdoc.c \
	   herdoc/utils_herdoc.c \
	  signals/signals.c\
	  utils_builtins/utils_export.c \
	  utils_builtins/utils_unset.c \
	  errors/handle_errors.c \
	  utils_execution/utils_pipe.c \
	  rederctions/rederction.c \
	  utils_execution/utils_exec_cmd.c \
	  utils_expand/linked_list_expd.c \
	  utils_expand/utils_expd.c \
	  utils_expand/utils_help_expd.c \
	  memory/free_list_env.c \
	  herdoc/error_and_herdoc.c \

OBJS = ${SRCS:.c=.o}

all : ${NAME}

%.o : %.c ${HEADER}
	${CC} ${CFLAGS} -I ${READLINE_I} -c $< -o $@

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -L ${READLINE_L} -lreadline

clean :
	${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : fclean all