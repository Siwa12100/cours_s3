#CC : le compilateur à utiliser
CC=gcc

#CFLAGS : les options de compilation
CFLAGS= -g -Wall

# les fichiers sources : tous les fichiers présents dans src/
SRC=$(wildcard src/*.c)

# les fichiers objets (.o)
OBJ=$(patsubst src/%.c,obj/%.o,$(SRC))


#edition des liens : génération de l'exécutable à partir des .o 
bin/exe: $(OBJ)
	$(CC) $(OBJ) -o $@

# génération des .o à partir des .c et .h crrespondants : 
obj/tests_abr.o: src/tests_abr.c 
	$(CC) $(CFLAGS) -c $< -o $@
obj/%.o: src/%.c src/%.h
	$(CC) $(CFLAGS) -c $< -o $@

#nettoyage : destruction des .o et de l'exécutable
clean:
	rm obj/*.o bin/exe
