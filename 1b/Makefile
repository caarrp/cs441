CXX = g++

CXXFLAGS= -Wall -g 

TARGET= 1B_out

$(TARGET): proj1B.cpp image.h
	   $(CXX) $(CXXFLAGS) -o $(TARGET) proj1B.cpp

run:
	./1B_out
	display 1B_out.pnm

clean:
	rm -f $(TARGET)

.PHONY: clean

