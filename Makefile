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

VAR = main.o Game.o Shader.o SplashScreen.o

#$(OBJ_DIR)/%.o : %.cpp
#	$(CC) $(INC) $(LIB) $(CPP_FLAGS) -o $@ $< 

all : main.o Game.o Shader.o SplashScreen.o Textures.o
	$(CC) $(LIB) $(INC) \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/Shader.o \
	$(OBJ_DIR)/Game.o \
	$(OBJ_DIR)/SplashScreen.o \
	$(OBJ_DIR)/Textures.o \
	-o main

main.o : main.cpp Game.o
	$(CC) -c main.cpp -o $(OBJ_DIR)/main.o

Game.o : Game.cpp Game.hpp 
	$(CC) -c Game.cpp -o $(OBJ_DIR)/Game.o

Shader.o : Shader.cpp Shader.hpp
	$(CC) -c Shader.cpp -o $(OBJ_DIR)/Shader.o

SplashScreen.o : SplashScreen.cpp SplashScreen.hpp
	$(CC) -c SplashScreen.cpp -o $(OBJ_DIR)/SplashScreen.o

Textures.o : Textures.cpp Textures.hpp
	$(CC) -c Textures.cpp -o $(OBJ_DIR)/Textures.o

run : all
	./main

.PHONY : clean

windows :
	g++ main.cpp  GLFW/libglfw3dll.a -L/usr/i686-pc-mingw32/sys-root/mingw/lib -lopengl32

clean : 
	rm -rf $(OBJ_DIR)/*.o
