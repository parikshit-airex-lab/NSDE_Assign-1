# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Target executable
TARGET = main

# Source files
SRCS = main.cpp utils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule: Build the target executable
all: $(TARGET)

# Rule to link the object files into the target executable
$(TARGET): $(OBJS)
	@echo "Linking object files to create the executable..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete. Executable: $(TARGET)"

# Rule to compile main.cpp into main.o
main.o: main.cpp
	@echo "Compiling main.cpp..."
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

# Rule to compile utils.cpp into utils.o
utils.o: utils.cpp
	@echo "Compiling utils.cpp..."
	$(CXX) $(CXXFLAGS) -c utils.cpp -o utils.o

# Clean rule to remove generated files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(OBJS)
	@echo "Clean complete."

# Phony targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean