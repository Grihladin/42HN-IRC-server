# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 13:24:12 by psenko            #+#    #+#              #
#    Updated: 2025/07/24 13:02:04 by mratke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=c++
NAME=ircserv
CFLAGS=-Wall -Wextra -Werror -std=c++17

SOURCES=Parser.cpp tests.cpp

HEADER=IRCMessage.h

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
