OBJDIR := obj
SRCDIR := src
BINDIR := bin

cppfiles := $(patsubst %.c,%.o,$(wildcard *.cpp))
exe := Beleg.exe

exe: $(cppfiles:.cpp=.o)
	g++ -o $(exe) $(cppfiles:.cpp=.o) -lglut -lGLU -lGL -lGLEW -lfreeimage
	./$(exe)
	mv $(exe) ../bin

$(cppfiles):

.PHONY: clean
clean:
	rm -f $(cppfiles:.cpp=.o) prog

