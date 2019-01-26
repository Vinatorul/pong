OBJS = src/main.cxx src/game.cxx src/rect.cxx
COMPILER_FLAGS = -O3 -std=c++14 -w
LINKER_FLAGS = -lSDL2 -lGL -lGLU -lGLEW
OBJ_NAME = bin/main
all : $(OBJS)
	mkdir -p bin
	g++ $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
run:
	./bin/main