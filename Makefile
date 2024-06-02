# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 22:38:40 by kahmada           #+#    #+#              #
#    Updated: 2024/05/31 06:41:52 by kahmada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
HEADER = Mandatory/pipex.h
HEADER_BONUS = Bonus/pipex_bonus.h
CFLAGS = -Wall -Wextra -Werror
SRCS = Mandatory/pipex.c Mandatory/ft_split.c Mandatory/utils_pipex.c Mandatory/paths.c Mandatory/ft_split_lib.c Mandatory/function_error.c
BONUS_SRCS = Bonus/pipex_bonus.c Bonus/utils_pipex_bonus.c Bonus/ft_split.c Bonus/here_doc.c Bonus/get_next_line.c Bonus/get_next_line_utils.c Bonus/paths_bonus.c Bonus/error_clean.c Bonus/here_doc_util.c Bonus/ft_split_lib_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME)

Mandatory/%.o: Mandatory/%.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

Bonus/%.o: Bonus/%.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all