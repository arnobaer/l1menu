.PHONY: all python clean

TARGET = l1menu

PYTHON = python3.6
SWIG = swig
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -g
INCDIRS = -I../include -I/usr/include/$(PYTHON)
LIBS = -lpugixml


all: python

python: _$(TARGET).so $(TARGET).py

_$(TARGET).so: $(TARGET)_wrap.o
	$(CXX) -shared $< $(LIBS) -o $@

$(TARGET)_wrap.o: $(TARGET)_wrap.cxx
	$(CXX) -c $(CXXFLAGS) -DSWIG -fpic $(INCDIRS) $< -o $@

$(TARGET)_wrap.cxx: $(TARGET).i
	$(SWIG) -python -c++ $<

clean:
	$(RM) _$(TARGET).so $(TARGET)_wrap.o $(TARGET)_wrap.cxx $(TARGET).py $(TARGET).pyc
