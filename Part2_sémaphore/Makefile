#Makefile cree par Vincent Boyer
#Septembre 2015

#definition des commandes
CC = gcc
RM = rm

#options du compilateur
CFLAGS = -I/opt/local/include
LDFLAGS = -L/opt/local/lib -lpng

#fichiers et dossiers
PROGNAME = third
HEADERS= readwritepng.h
SRC = $(wildcard *.c) 
OBJ = $(SRC:.c=.o)

all: $(PROGNAME)

$(PROGNAME) : $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c


clean:
	$(RM) -f $(OBJ) *~ $(PROGNAME)

