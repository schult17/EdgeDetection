# Makefile for edge detection compilation

# ***********************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g
TARGET = edgedetection

# ***********************************************
# Targets needed to bring the executable up to date

$(TARGET) : main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o

# The main.o target written more simply
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp



# ***********************************************
# Clean rule
clean:
	rm -f $(TARGET)
	rm -f main.o

