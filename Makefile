# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 13:24:12 by psenko            #+#    #+#              #
#    Updated: 2025/07/22 19:48:29 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=c++
NAME=ircserv
CFLAGS=-Wall -Wextra -Werror -std=c++17

SOURCES=main.cpp ParsedCommand.cpp

HEADER=

OBJECTS=$(SOURCES:.cpp=.o)

all: $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

$(NAME): $(OBJECTS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean fclean re
