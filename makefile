# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Target executable
TARGET = proj4

# Source files and objects
SRCS = proj4_driver.cpp
OBJS = proj4_driver.o

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile the main driver file
proj4_driver.o: proj4_driver.cpp bet.hpp bet.h
	$(CXX) $(CXXFLAGS) -c proj4_driver.cpp

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)