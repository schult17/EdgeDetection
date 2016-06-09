# Makefile for edge detection compilation

# ***********************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g
LIBPATH = -L/usr/local/libjpeg-9b/lib/
LIBS = -ljpeg
TARGET = edgedetection
OBJ = main.o JpegImage.o stringhelpers.o

# ***********************************************
# Targets needed to bring the executable up to date

$(TARGET) : $(OBJ)
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(LIBPATH) $(LIBS) $(OBJ) -o $(TARGET)

# The main.o target written more simply
main.o: main.cpp JpegImage.h JpegImage.cpp stringhelpers.cpp stringhelpers.h
	$(CXX) $(CXXFLAGS) -c main.cpp

JpegImage.o : JpegImage.h JpegImage.cpp
stringhelpers.o : stringhelpers.h stringhelpers.cpp

# ***********************************************
# Clean rule
clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -f *~

