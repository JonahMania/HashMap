NAME = testHashmap
SRC = testHashmap.cpp

OBJ = $(SRC:.cpp=.o)
RM = rm -f
all: $(OBJ) 
		g++ $(OBJ) -g -o $(NAME)

clean:
		-$(RM) *.o
		-$(RM) *.core

