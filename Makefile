# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melachyr <melachyr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 14:39:33 by melachyr          #+#    #+#              #
#    Updated: 2024/02/20 23:43:07 by melachyr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -Wall -Wextra -Werror
NAME = pipex
SRCS = libft/ft_split.c libft/ft_split_2.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strcmp.c\
	   libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_putstr_fd.c\
	   exceptions/exceptions.c utils/get_cmd_location.c utils/get_cmd.c utils/processes.c utils/pipes.c utils/cmds.c\
	   pipex.c init_vars.c\
	   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS) #-fsanitize=address -g3
	$(CC) $(CFLAGS) $(OBJS) -o $@

bonus: $(OBJS) #-fsanitize=address -g3
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re