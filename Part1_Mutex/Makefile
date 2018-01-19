#Makefile cree par Vincent Boyer
#Septembre 2015
# modifié par aoudjit # Janvier 2018 


#definition des commandes
CC = gcc
RM = rm

#options du compilateur
CFLAGS =  -Wall 
LDFLAGS = -lpthread


#fichiers et dossiers
PROGNAME = Part1_Mutex
HEADERS= sens.h
SRC = $(wildcard *.c) 
OBJ = $(SRC:.c=.o)

all: $(PROGNAME)

$(PROGNAME) : $(OBJ)
	$(CC) $(CFLAGS) $^  -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $< -c $(LDFLAGS)


clean:
	$(RM) -f $(OBJ) *~ $(PROGNAME)

