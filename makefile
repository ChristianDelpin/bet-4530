# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = proj4.x

# Source and header files
SOURCES = proj4_driver.cpp
HEADERS = bet.h bet.hpp

# Build target
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean target
clean:
	rm -f $(TARGET)