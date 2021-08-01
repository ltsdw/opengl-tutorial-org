SRC_DIR=src
SRC=$(shell find $(SRC_DIR) -name "*.cpp")

CXXFLAG=-Wall
LDFLAGS=-lGL -lglfw -lGLEW -lglfw

all:
	$(CXX) $(CXXFLAG) $(LDFLAGS) $(SRC) -o red_triangle 
