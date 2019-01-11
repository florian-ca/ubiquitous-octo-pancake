OBJ_DIR=obj
SRC_DIR=src

SRC=$(shell find $(SRC_DIR) -name "*.cpp")
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

EXEC=../ParserPdf
INCPATH=./include/

comp_exec: all

all: main.cpp $(OBJ)
	@g++ -std=c++11 $< -I$(INCPATH) $(OBJ) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++11 -I$(INCPATH) -c $< -o $@
