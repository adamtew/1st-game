CC = g++
CPP_FLAGS = -lglfw -framework OpenGL
INC = -Isoil2/src/SOIL2/ 
LIB = -Lsoil2/lib/macosx -lsoil2-debug -lglfw -lglew -framework OpenGL -framework CoreFoundation
EXE = main

main : main.cpp Game.cpp Game.hpp SplashScreen.cpp SplashScreen.hpp
	$(CC) $(INC) $(LIB) $(CPP_FLAGS) main.cpp Game.cpp SplashScreen.cpp -o $(EXE)

run : $(EXE)
	./main
