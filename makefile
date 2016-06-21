# Makefile for edge detection compilation

# ***********************************************
# Variables to control Makefile operation
CXX = g++
CXXLINKER = g++ -o
CXXFLAGS = -Wall -g -std=c++11 -I$(HDIR)
TARGET = edgedetection

# ***********************************************
# Names of directories for source (.cpp),
# headers (.h), objects (.o) and the program (.exe)
SRCDIR = src
HDIR = h
OBJDIR = obj
BINDIR = .

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(HDIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# ***********************************************
# Targets needed to bring the executable up to date

# Linking the object files into the target executable 
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(CXXLINKER) $@ $(CCFLAGS) $(OBJECTS)
	@echo "Done"

# Compiling the source files into objects
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compilation of "$<" complete"

# Making object and binary directories if they
# do not currently exist (-p) [bin/ and obj/]
all: $(OBJECTS)
$(OBJECTS): | $(OBJDIR)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# ***********************************************
# Clean rule: remove 
.PHONEY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR)
	rm -f $(BINDIR)/$(TARGET)
	@rm -f *~
	@echo "Done"
