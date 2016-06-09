# Makefile for edge detection compilation

# ***********************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -g
LIBPATH = -L/usr/local/libjpeg-9b/lib/
LIBS = -ljpeg
TARGET = edgedetection
OBJ = main.o JpegImage.o stringhelpers.o EdgeDetector.o
BINDIR = bin

# ***********************************************
# Targets needed to bring the executable up to date

$(TARGET) : $(OBJ)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $(LIBPATH) $(LIBS) $(OBJ) -o $(TARGET)
	@mv *.o ./$(BINDIR)

# The main.o target written more simply
main.o: main.cpp JpegImage.h JpegImage.cpp stringhelpers.cpp stringhelpers.h
	$(CXX) $(CXXFLAGS) -c main.cpp

EdgeDetector.o: EdgeDetector.h EdgeDetector.cpp JpegImage.h JpegImage.cpp
JpegImage.o : JpegImage.h JpegImage.cpp
stringhelpers.o : stringhelpers.h stringhelpers.cpp

# ***********************************************
# Clean rule
clean:
	rm -f $(TARGET)
	rm -rf $(BINDIR)
	rm -f *~

