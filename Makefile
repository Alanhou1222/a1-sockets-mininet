CXX = g++
CXXFLAGS = -g -std=c++14 -pedantic

server: server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client

iPerfer: iPerfer.cpp
	$(CXX) $(CXXFLAGS) functions.cpp iPerfer.cpp -o iPerfer

clean:
	rm client server iPerfer

.PHONY: clean