#MAKEFILE By: Afonso Salvador de Magalhaes

COMP = compacta.out
DESC = descompacta.out
CC = gcc
FLAGS = -pedantic -lm -Wall
DIR_MAINS = Mains
FOLDER = Executaveis

UNIVERSAL_C = arvore.o bitmap.o compactador.o lista.o compacta.o

UNIVERSAL_D = arvore.o bitmap.o descompactador.o lista.o descompacta.o

CYAN = "\033[1;36m"
YELLOW = "\033[1;33m"
WHITE = "\033[1;37m"
RED = "\033[1;31m"
RESET = "\033[0m"

all : o_files create_executable create_dir


o_files : 
	@ echo $(CYAN)
	@ echo "Compilando arquivos..."
	@ $(CC) -c *.c
	@ $(CC) -c $(DIR_MAINS)/*.c
	@ echo $(RESET)

create_executable: 
	@ echo $(CYAN)
	@ echo "Criando executaveis..."
	@ $(CC) -o $(COMP) $(UNIVERSAL_C)
	@ $(CC) -o $(DESC) $(UNIVERSAL_D)
	@ echo $(RESET)

create_dir:
	@ echo $(WHITE)
	@ echo "Criando pasta..."
	@mkdir $(FOLDER)
	@mv $(COMP) $(DESC) ./$(FOLDER)
	@ echo $(RESET)

clean:
	@ echo $(RED)
	@ echo "Removendo arquivos gerais ..."
	@ rm -rf *.o ./$(FOLDER) 
	@ echo $(RESET)

clear:
	@ clear
	@ echo $(YELLOW)
	@ echo "Removendo arquivos temporarios ..."
	@ rm -rf *.o 
	@ echo $(RESET)
