CXX = g++

CXXFLAGS = -Wall -Wextra -g

LDFLAGS = -lws2_32

SERVER = server


SRCS = server.cpp
OBJS = $(SRCS:.cpp=.o)

LIBS = -lws2_32

all: $(SERVER)

$(SERVER): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(SERVER)