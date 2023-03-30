all: game.exe

CXX=g++
CFLAGS=-Wall -Wextra -Wpedantic -Werror

game.exe: src/game.cpp
	${CXX} ${CFLAGS} $^ -o $@

clean:
	del /F /Q game.exe