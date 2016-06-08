# Makefile for edge detection compilation

# ***********************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g
LIBPATH = -L/usr/local/libjpeg-9b/lib/
LIBS = -ljpeg
TARGET = edgedetection

# ***********************************************
# Targets needed to bring the executable up to date

$(TARGET) : main.o
	$(CXX) $(CXXFLAGS) $(LIBPATH) $(LIBS) -o $(TARGET) main.o

# The main.o target written more simply
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp



# ***********************************************
# Clean rule
clean:
	rm -f $(TARGET)
	rm -f main.o

