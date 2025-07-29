# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mratke <mratke@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2025/07/30 00:32:09 by mratke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -g -fsanitize=address
SRC_DIR = src
OBJ_DIR = obj

SRC=		main.cpp \
			IrcServer.cpp \
			Channel.cpp \
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
			Commands/Ping.cpp \
			Commands/Pong.cpp \
			Commands/PrivMsg.cpp \
			Commands/Quit.cpp \
			Commands/Topic.cpp \
			Commands/User.cpp \
			Commands/Pass.cpp \
			Commands/Wrong.cpp \
			Commands/Who.cpp \
			Parser.cpp \
			IrcServer/getNickList.cpp \
			IrcServer/getChannel.cpp \
			IrcServer/DeleteUserFromChannel.cpp \
			IrcServer/sendToFd.cpp \
			IrcServer/sendMessage.cpp \
			IrcServer/handleClient.cpp \
			IrcServer/connectIsSuccesfull.cpp

HEADER=		Include/Channel.hpp \
			Include/Command.hpp \
			Include/IrcServer.hpp \
			Include/User.hpp \
			Include/Definitions.hpp

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
