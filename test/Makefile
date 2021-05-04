.PHONY: all python clean

TARGET = test
TEST_SRC = test.cc
TEST_OBJ = $(TEST_SRC:%.cc=%.o)

CXX = clang++
CXXFLAGS = -std=c++11 -g -Wall
INCDIRS = -I../include

all: $(TARGET)

$(TARGET): $(TEST_OBJ)
	$(CXX) $< -lpugixml -o $@

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(INCDIRS) $< -o $@

clean:
	$(RM) $(TARGET) $(TEST_OBJ)
