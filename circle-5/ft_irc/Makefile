NAME		= ircserv

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS		= main.cpp \
			  src/Server.cpp src/Messages.cpp src/Client.cpp src/Channel.cpp src/Utils.cpp \
			  cmd/Pass.cpp cmd/Nick.cpp cmd/User.cpp cmd/Ping.cpp cmd/Quit.cpp \
			  cmd/Join.cpp cmd/Part.cpp cmd/Privmsg.cpp cmd/Who.cpp \
			  cmd/Kick.cpp cmd/Invite.cpp cmd/Topic.cpp cmd/Mode.cpp
HEADERS		= inc/Server.hpp inc/Client.hpp inc/Channel.hpp inc/Replies.hpp inc/Utils.hpp

OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

# rebuild an object when a header changes
$(OBJS): $(HEADERS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
