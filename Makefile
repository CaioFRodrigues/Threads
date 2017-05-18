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

regra1: internal.o semaforo.o threads.o testes.o
	$(CC) -o exec $(BIN_DIR)internal.o $(BIN_DIR)semaforo.o $(BIN_DIR)threads.o $(BIN_DIR)support.o $(BIN_DIR)testes.o -Wall -m32

internal.o: $(SRC_DIR)internal.c
	$(CC) -o $(BIN_DIR)internal.o -c $(SRC_DIR)internal.c -Wall -m32

semaforo.o: $(SRC_DIR)semaforo.c
	$(CC) -o $(BIN_DIR)semaforo.o -c $(SRC_DIR)semaforo.c -Wall -m32

threads.o: $(SRC_DIR)threads.c
	$(CC) -o $(BIN_DIR)threads.o -c $(SRC_DIR)threads.c -Wall -m32

testes.o: $(TST_DIR)test_with_csetprio.c 	#Dunno if the testes is exactly right
	$(CC) -o $(BIN_DIR)testes.o -c $(TST_DIR)test_with_csetprio.c -Wall -m32


clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/internal.o $(BIN_DIR)/semaforo.o $(BIN_DIR)/threads.o $(BIN_DIR)/testes.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ 
