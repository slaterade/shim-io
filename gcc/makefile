# amateur attempt a a makefile

SHELL = /bin/sh
CXX = g++
FLAGS = -std=c++11 -pthread
CXXFLAGS = -Wall

TARGET = shimmy
SOURCE = $(shell echo ../source/*.cpp)

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(FLAGS) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

