CC = g++
CPP_FLAGS = -lglfw -framework OpenGL
#INCLUDE = -I/usr/local/lib -L/usr/local/share -lsoil2-debug 
INC = -Isoil2/src/SOIL2/ 
LIB = -Lsoil2/lib/macosx -lsoil2-debug -lglfw -framework OpenGL -framework CoreFoundation
EXE = ./main.out

# will probably need -lSOIL befor -lopengl

main : main.cpp Game.cpp Game.hpp SplashScreen.cpp SplashScreen.hpp
	$(CC) $(INC) $(LIB) $(CPP_FLAGS) main.cpp Game.cpp SplashScreen.cpp -o main.out
	#$(CC) $(INCLUDE) $(CPP_FLAGS) main.cpp Game.cpp SplashScreen.cpp -o main

run : $(EXE)
	$(EXE)

#g++ -Isoil2/src/SOIL2/ -Lsoil2/lib/macosx -lsoil2-debug -lglfw -framework OpenGL -framework CoreFoundation  main.cpp -o main
