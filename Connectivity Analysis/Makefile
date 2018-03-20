SOURCE = main.cpp \
        set.cpp\
		inputHandler.cpp \
		alloc2d.cpp \
		graphics.cpp \
		lodepng.cpp \
		psuedo.cpp \
		readpng.cpp \
		callbacks.cpp\
		initState.cpp\
		display.cpp\
		keyboard.cpp\
		analysis.cpp


OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11
CXXFLAGS = $(CFLAGS)

TARGET = conncomp

# Fill in special libraries needed here
LIBS = -lglut -lGLU -lGL -lpthread

.PHONY: clean

# Targets include all, clean, debug, tar

all : conncomp

conncomp: $(OBJS)
	$(LINK) -o conncomp $^ $(LIBS)

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

