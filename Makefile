# $@ : $^
CC = g++
CPP_FLAGS = -lglfw -framework OpenGL
INC = -Isoil2/src/SOIL2/ 
LIB = -Lsoil2/lib/macosx -lsoil2-debug -lglfw -lglew -framework OpenGL -framework CoreFoundation
OBJ_DIR = obj
EXE = main
DEP = main.cpp

SRC = ./*.hpp

#$(OBJ_DIR)/%.o : %.cpp $(EXE)
#	$(CC) -c -o $@ $< $(CFLAGS) $(LIB) $(INC)

#$(OBJ_DIR)/main.o : main.cpp SplashScreen.cpp SplashScreen.hpp
#	$(CC) $(INC) $(LIB) $(CPP_FLAGS) main.cpp Game.cpp SplashScreen.cpp -o $(EXE)

VAR = main.o Game.o Shaders.o SplashScreen.o

#$(OBJ_DIR)/%.o : %.cpp
#	$(CC) $(INC) $(LIB) $(CPP_FLAGS) -o $@ $< 

all : main.o Game.o Shaders.o SplashScreen.o Textures.o
	$(CC) $(LIB) $(INC) \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/Shaders.o \
	$(OBJ_DIR)/Game.o \
	$(OBJ_DIR)/SplashScreen.o \
	$(OBJ_DIR)/Textures.o \
	-o main

main.o : main.cpp Game.o
	$(CC) -c main.cpp -o $(OBJ_DIR)/main.o

Game.o : Game.cpp Game.hpp 
	$(CC) -c Game.cpp -o $(OBJ_DIR)/Game.o

Shaders.o : Shaders.cpp Shaders.hpp
	$(CC) -c Shaders.cpp -o $(OBJ_DIR)/Shaders.o

SplashScreen.o : SplashScreen.cpp SplashScreen.hpp
	$(CC) -c SplashScreen.cpp -o $(OBJ_DIR)/SplashScreen.o

Textures.o : Textures.cpp Textures.hpp
	$(CC) -c Textures.cpp -o $(OBJ_DIR)/Textures.o

run : all
	./main

.PHONY : clean

clean : 
	rm -rf $(OBJ_DIR)/*.o
