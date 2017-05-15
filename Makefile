#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib/
INC_DIR=./include/
BIN_DIR=./bin/
SRC_DIR=./src/
TST_DIR=./testes/

all: regra1

regra1: internal.o semaforo.o threads.o testes.c
	$(CC) -o $(BIN_DIR)internal.o $(BIN_DIR)semaforo.o $(BIN_DIR)threads.o exec -Wall

internal.o: $(SRC_DIR)internal.c
	$(CC) -c $(SRC_DIR)internal.c -Wall

semaforo.o: $(SRC_DIR)semaforo.c
	$(CC) -c $(SRC_DIR)semaforo.c -Wall

threads.o: $(SRC_DIR)threads.c
	$(CC) -c $(SRC_DIR)threads.c -Wall

testes.c: $(TST_DIR)testes.c 	#Dunno if the testes is exactly right
	$(CC) -c $(TST_DIR)testes.c -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/internal.o $(BIN_DIR)/semaforo.o $(BIN_DIR)/threads.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~