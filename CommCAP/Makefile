CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE_MONGO	:= /usr/local/include/mongocxx/v_noabi
INCLUDE_BSON	:= /usr/local/include/bsoncxx/v_noabi
LIB     := lib

LIBRARIES	:= -lmongocxx -lbsoncxx
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_MONGO) -I$(INCLUDE_BSON) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
