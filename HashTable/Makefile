# Makefile example code
#
# Author: Paul Hinker
#
# Purpose: CSC 315 Data Structures & Algorithms - Fall 2017
#
# Date: Sept. 2017
#
SOURCE = main.cpp \
	 	 usage.cpp \
	 	 Hash.cpp \
		 readandwrite.cpp\
		 HelperFunctions.cpp\

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11
CXXFLAGS = $(CFLAGS)

TARGET = zipf

.PHONY: clean

# Targets include all, clean, debug, tar

all : zipf

zipf: $(OBJS)
	 $(LINK) -o zipf $^ $(CXXFLAGS)

clean:
	rm -rf *.o *.d core $(TARGET) 

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: $(TARGET) 

tar: clean
	tar zcvf $(TARGET).tgz $(SOURCE) *.h Makefile

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

