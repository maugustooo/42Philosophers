# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 11:06:36 by maugusto          #+#    #+#              #
#    Updated: 2024/10/24 15:40:19 by maugusto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g
LDFLAGS		= -lpthread -fsanitize=thread

NAME		= philo

INC			= -I./includes
RM			= rm -rf

GENERAL		= main
SRC_DIR		= utils parse routine init monitor

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH		= src 

SRC			= $(addsuffix .c, $(GENERAL))\
			  $(addsuffix .c, $(SRC_DIR))\

OBJ_DIR		= obj

OBJS		= $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	@$(RM) $(OBJS) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME) $(OBJ_DIR)

re: fclean all