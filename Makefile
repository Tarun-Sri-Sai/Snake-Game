CXX=g++
CFLAGS=-Wall -Wextra -Wpedantic -Werror
FILE=game
BIN=bin
SRC=src

all: $(BIN)/$(FILE).exe

$(BIN)/$(FILE).exe: $(SRC)/$(FILE).cpp
	${CXX} ${CFLAGS} $^ -o $@

run:
	$(BIN)/$(FILE).exe

clean:
	del /F /Q game.exe