NAME = soft-war

LD = gcc

RM = rm -f

OBJ = src/*.c lib/*.c

CFLAGS += -g -W -Werror -Wall

all:
	$(LD) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -rf *.o src/*.o lib/*.o

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
