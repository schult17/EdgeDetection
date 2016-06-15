# Makefile for edge detection compilation

# ***********************************************
# Variables to control Makefile operation
CXX = g++
CXXFLAGS = -Wall -g -I$(HDIR)
LINKER = g++ -o
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
$(BINDIR)/$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@$(LINKER) $@ $(CCFLAGS) $(OBJECTS)
	@echo "Done"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compilation of "$<" complete"

# Making object and binary directories if they
# do not currently exist (-p)
all: $(OBJECTS)
$(OBJECTS): | $(OBJDIR)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# ***********************************************
# Clean rule: remove 
.PHONEY: clean
clean:
	@echo "Cleaning..."
	@rm -rf $(OBJDIR)
	@rm -f $(BINDIR)/$(TARGET)
	@rm -f *~
	@echo "Done"
