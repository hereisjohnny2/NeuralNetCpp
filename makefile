#Define o nome do projeto
PROJ_NAME=main

#Define o nome do executável
EXE_NAME=neural

#Define a pata onde estão os arquivos c++
CPP_SOURCE=$(wildcard ./source/*.cpp)

#Define as pastas onde estão os arquvos de cabeçalho
HPP_SOURCE=$(wildcard ./source/headers/*.hpp)

#Define o nome dos arquivos objetos de acordo com o nome dos arquivos em c++
OBJ=$(subst .cpp,.o,$(subst source,objects,$(CPP_SOURCE)))

#Define o compilador utilizado
CC=g++

#Define a versão da linguagem
CC_VERSION=c++14

#Define a as flags utilizadas junto com o compilador
#	-c			-> 
#	-W 			-> Exibe avisos de forma verbosa
#	-Wall 		-> Ativa a exibição de diversos tipos de avisos (warnings)
#	-ansi 		-> 
#	-pedantic 	-> Ativa os avisos relacionados com ISO C++ e ISO C
CC_FLAGS=-c			\
		 -W 		\
		 -Wall		\
		 -ansi		\
		 -pedantic	\
		 -std=$(CC_VERSION)

#Define o comando do shell para remover arquivos
#	rm			-> comando para remover arquivos
#	r			-> permite a remoção de diretórios
#	f			-> ignora arquivos e argumentos não existentes
RM=rm -rf

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Construindo binários usando gcc linker: $@'
	$(CC) $^ -o $(EXE_NAME)
	@ echo 'Construção dos binario finalizada: $@'
	@ echo ' '

./objects/%.o: ./source/%.cpp ./source/headers/%.hpp
	@ echo 'Compilando o código utilizando GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./source/main.cpp $(HPP_SOURCE)
	@ echo 'Compilando o código utilizando GCC: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder: 
	@ mkdir -p objects

clean:
	@ $(RM) ./objects/*.o $(EXE_NAME) *~
	@ rmdir objects

memcheck:
	valgrind --leak-check=yes -s ./$(EXE_NAME)

.PHONY: all clean