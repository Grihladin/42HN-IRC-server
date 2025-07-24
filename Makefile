# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psenko <psenko@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 13:24:12 by psenko            #+#    #+#              #
#    Updated: 2025/07/24 11:43:38 by psenko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=c++
NAME=ircserv
CFLAGS=-Wall -Wextra -Werror -std=c++17

SOURCES=src/main.cpp \
			src/IrcServer.cpp \
			src/Channel.cpp \
			src/Message.cpp \
			src/User.cpp \
			src/Command.cpp \
			src/IrcServerCommands.cpp \
			src/IrcServerParser.cpp \
			src/IrcServerCommandExecutor.cpp

HEADER=Include/Channel.hpp \
		Include/Command.hpp \
		Include/IrcServer.hpp \
		Include/Message.hpp \
		Include/User.hpp 

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
