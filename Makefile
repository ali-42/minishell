# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ali <ali@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 14:50:00 by ali               #+#    #+#              #
#    Updated: 2022/02/03 23:23:37 by ali              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = \
sources/builtins/ft_cd_back.c     sources/parsing/parse.c \
sources/builtins/ft_cd.c          sources/parsing/parse_error.c \
sources/builtins/ft_echo.c \
sources/builtins/ft_env.c         sources/parsing/quotes.c \
sources/builtins/ft_exit.c        sources/parsing/split.c \
sources/builtins/ft_exit_utils.c  sources/parsing/split_utils.c \
sources/builtins/ft_export.c      sources/parsing/variables.c \
sources/builtins/ft_pwd.c         sources/parsing/variables_utils2.c \
sources/builtins/ft_unset.c       sources/parsing/variables_utils.c \
sources/env/add_to_env.c          sources/readline/readline.c \
sources/env/env_to_char2.c        sources/redir/check_file.c \
sources/env/get_env.c             sources/redir/create_pipe.c \
sources/env/is_in_env.c           sources/redir/redir.c \
sources/env/parse_env.c           sources/signals/signals.c \
sources/env/set_env.c             sources/utils/char2_dup.c \
sources/exec/exec_all_cmd.c       sources/utils/ft_atoi.c \
sources/exec/exec_builtin.c       sources/utils/ft_isdigit.c \
sources/exec/exec_cmd.c           sources/utils/ft_itoa.c \
sources/exec/is_builtin.c         sources/utils/ft_memcpy.c \
sources/free/free_char2.c         sources/utils/ft_putchar_fd.c \
sources/free/free_cmd.c           sources/utils/ft_putendl_fd.c \
sources/free/free_env.c           sources/utils/ft_putstr_fd.c \
sources/free/free_file.c          sources/utils/ft_split.c \
sources/free/free_shell.c         sources/utils/ft_strcmp.c \
sources/main/minishell.c          sources/utils/ft_strdup.c \
sources/parsing/commands.c        sources/utils/ft_strjoin3.c \
sources/parsing/commands_utils.c  sources/utils/ft_strlcat.c \
sources/parsing/files.c           sources/utils/ft_strlcpy.c \
sources/parsing/nospaces.c        sources/utils/ft_strlen.c \
sources/exec/exec_cmd_utils.c     sources/redir/check_file_utils.c \
sources/builtins/check_invalid.c	sources/redir/create_all_heredoc.c \
sources/parsing/ft_variables_heredoc.c	sources/redir/already_open.c \
sources/builtins/ft_pwd_redir.c	sources/builtins/ft_env_redir.c \
sources/builtins/ft_echo_redir.c	sources/exec/exec_builtin_redir.c \
sources/builtins/ft_cd_path.c		sources/builtins/ft_cd_path_redir.c \
sources/builtins/ft_export_noarg.c 	sources/builtins/ft_export_utils.c \
sources/builtins/ft_export_arg.c	sources/utils/ft_strjoin.c \
sources/parsing/split_utils2.c		sources/redir/heredoc_utils.c \
sources/redir/heredoc_utils2.c		sources/parsing/quotes_utils.c \
sources/free/free_shell_execve.c	sources/parsing/variables_utils3.c \
sources/exec/exec_all_cmd_utils.c	sources/parsing/variables_utils4.c
HEADER = ./includes/
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I $(HEADER)
RM = rm -f

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)
