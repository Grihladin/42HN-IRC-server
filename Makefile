# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/07/24 21:15:03 by auplisas         ###   ########.fr        #
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
			src/IrcServerParser.cpp \
			src/IrcServerCommandExecutor.cpp \
			src/Commands/Invite.cpp \
			src/Commands/Join.cpp \
			src/Commands/Kick.cpp \
			src/Commands/List.cpp \
			src/Commands/Mode.cpp \
			src/Commands/Nick.cpp \
			src/Commands/Oper.cpp \
			src/Commands/Part.cpp \
			src/Commands/PrivMsg.cpp \
			src/Commands/Quit.cpp \
			src/Commands/Topic.cpp \
			src/Commands/User.cpp \
			src/Commands/Pass.cpp \

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
