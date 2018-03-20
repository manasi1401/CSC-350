# Makefile for OpenGLDemo example code
#
# Author: Paul Hinker
#
# Purpose: CSC 300 Data Structures & Algorithms - Fall 2016
#
# Date: Sep. 3, 2016
#
SOURCE = main.cpp \
         HuffmanBinaryTree.cpp \
         decoder.cpp \
	 encoder.cpp \

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -g -std=c++11
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = -lglut -lGLU -lGL -lpthread

.PHONY: clean

# Targets include all, clean, debug, tar

all : huffman  

huffman: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core huffman

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: huffman

tar: clean
	tar zcvf huffman.tgz $(SOURCE) *.h Makefile

help:
	@echo "	make main  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core main"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; /usr/bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

