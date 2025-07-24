# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auplisas <auplisas@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/07/25 00:43:05 by auplisas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
SRC_DIR = src
OBJ_DIR = obj

SRC=		main.cpp \
			IrcServer.cpp \
			Channel.cpp \
			Message.cpp \
			User.cpp \
			Command.cpp \
			IrcServerParser.cpp \
			IrcServerCommandExecutor.cpp \
			Commands/Invite.cpp \
			Commands/Join.cpp \
			Commands/Kick.cpp \
			Commands/List.cpp \
			Commands/Mode.cpp \
			Commands/Nick.cpp \
			Commands/Oper.cpp \
			Commands/Part.cpp \
			Commands/PrivMsg.cpp \
			Commands/Quit.cpp \
			Commands/Topic.cpp \
			Commands/User.cpp \
			Commands/Pass.cpp \
			Parser.cpp \
			parserTests.cpp

HEADER=		Include/Channel.hpp \
			Include/Command.hpp \
			Include/IrcServer.hpp \
			Include/Message.hpp \
			Include/User.hpp \
			Include/Definitions.hpp

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
