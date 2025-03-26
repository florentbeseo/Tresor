EXEC= game.elf

RM = rm -f

CC = gcc

CCFLAGS = -Wall -g -IPackages -MMD -MP

LDFLAGS = -lm

SRC = $(wildcard *.c */*.c) #*/*.c icnlu tout les fichier .c dans les racines inférieurs
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)
#compilation rules
all: $(EXEC)

$(EXEC):$(OBJ)#main.o package/exemple.o
	$(CC) $^ -o $@ $(LDFLAGS)

-include $(DEP)

#main.o: package/exemple.h
#gcc -Wall -c main.c -o main.o
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@
#package/exemple.o:package/exemple.c


#clean the project
clean:
	$(RM) $(OBJ) $(DEP) $(EXEC)#rm -f *.o prog.elf
