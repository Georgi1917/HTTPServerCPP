CXX = g++

CXXFLAGS = -Wall -Wextra -g

LDFLAGS = -lws2_32

SERVER = server

# Source files
SERVER_SRC = server.cpp

all: $(SERVER)

# Compile server
$(SERVER): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) $(SERVER_SRC) -o $(SERVER) $(LDFLAGS)

clean:
	rm -f $(SERVER)