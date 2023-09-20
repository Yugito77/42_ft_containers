# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 16:59:43 by hcherpre          #+#    #+#              #
#    Updated: 2023/02/09 16:28:06 by hcherpre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m

NAME =	Containers

RM = rm -rf

SRCS =	main.cpp $(wildcard tests/*.cpp)

CXX = g++

OBJS_PATH = objects/

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))

CXXFLAGS = -Wall -Werror -Wextra -DLIB=ft -std=c++98 -fsanitize=address -g3

$(OBJS_PATH)%.o: %.cpp $(wildcard Includes/*.hpp)
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

$(NAME):    $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "$(GREEN)Compilation OK!"


clean:
	@$(RM) $(OBJS_PATH)

fclean:			clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Cleaning OK!"

re:				fclean all

.PHONY:			all clean fclean re