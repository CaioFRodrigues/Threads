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
CONDITIONS=-Wall -m32
all: regra1

regra1: internal.o semaforo.o threads.o testes.o init.o manager.o
	$(CC) -o exec $(BIN_DIR)internal.o $(BIN_DIR)semaforo.o $(BIN_DIR)init.o $(BIN_DIR)threads.o $(BIN_DIR)/manager.o $(BIN_DIR)support.o $(BIN_DIR)testes.o $(CONDITIONS)

internal.o: $(SRC_DIR)internal.c
	$(CC) -o $(BIN_DIR)internal.o -c $(SRC_DIR)internal.c $(CONDITIONS)

semaforo.o: $(SRC_DIR)semaforo.c
	$(CC) -o $(BIN_DIR)semaforo.o -c $(SRC_DIR)semaforo.c $(CONDITIONS)

threads.o: $(SRC_DIR)threads.c
	$(CC) -o $(BIN_DIR)threads.o -c $(SRC_DIR)threads.c $(CONDITIONS)

init.o: $(SRC_DIR)init.c
	$(CC) -o $(BIN_DIR)init.o -c $(SRC_DIR)init.c $(CONDITIONS)

manager.o: $(SRC_DIR)manager.c
	$(CC) -o $(BIN_DIR)manager.o -c $(SRC_DIR)manager.c $(CONDITIONS)

testes.o: $(TST_DIR)I_am_the_future_test.c 	#Dunno if the testes is exactly right
	$(CC) -o $(BIN_DIR)testes.o -c $(TST_DIR)I_am_the_future_test.c $(CONDITIONS)


clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/internal.o $(BIN_DIR)/init.o $(BIN_DIR)/manager.o  $(BIN_DIR)/semaforo.o $(BIN_DIR)/threads.o $(BIN_DIR)/testes.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ 
