CXX = g++
CXXFLAGS = -g -std=c++17 -pedantic

iPerfer: iPerfer.cpp
	$(CXX) $(CXXFLAGS) functions.cpp iPerfer.cpp -o iPerfer

clean:
	rm iPerfer *.o

.PHONY: clean