# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/10/02 17:02:36 by mratke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
SRC_DIR = src
OBJ_DIR = obj

SRC=		Core/main.cpp \
			Core/IrcServer.cpp \
			Core/Channel.cpp \
			Core/User.cpp \
			Core/Command.cpp \
			Core/IrcServerParser.cpp \
			Core/IrcServerCommandExecutor.cpp \
			Commands/Invite.cpp \
			Commands/Join.cpp \
			Commands/Kick.cpp \
			Commands/List.cpp \
			Commands/Mode.cpp \
			Commands/Nick.cpp \
			Commands/Oper.cpp \
			Commands/Part.cpp \
			Commands/Ping.cpp \
			Commands/Pong.cpp \
			Commands/PrivMsg.cpp \
			Commands/Quit.cpp \
			Commands/Topic.cpp \
			Commands/User.cpp \
			Commands/Pass.cpp \
			Commands/Wrong.cpp \
			Commands/Who.cpp \
			Core/Parser.cpp \
			Core/getNickList.cpp \
			Core/getChannel.cpp \
			Core/DeleteUserFromChannel.cpp \
			Core/sendToFd.cpp \
			Core/sendMessage.cpp \
			Core/handleClient.cpp \
			Core/connectIsSuccesfull.cpp \
			Core/listenSocket.cpp

HEADER=		inc/Channel.hpp \
			inc/Command.hpp \
			inc/IrcServer.hpp \
			inc/User.hpp \
			inc/Definitions.hpp \
			Makefile

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER)
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
