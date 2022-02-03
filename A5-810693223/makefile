UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
		HEAD := \"sdlheaders/mac.hpp\"
  	CCFLAGS= -framework SDL2 -framework SDL2_image -framework SDL2_ttf
else
		HEAD := \"sdlheaders/linux.hpp\"
		CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
endif

all: game rsdl.o head

game: brickbreaker.o gameplay.o rsdl.o
		g++ example/main.cpp src/rsdl.o example/brickbreaker.o example/gameplay.o $(CCFLAGS) -o game

brickbreaker.o: example/brickbreaker.cpp gameplay.o rsdl.o
	g++ -c example/brickbreaker.cpp -o example/brickbreaker.o

gameplay.o: example/gameplay.cpp rsdl.o
	g++ -c example/gameplay.cpp -o example/gameplay.o

rsdl.o: src/rsdl.hpp src/rsdl.cpp
		g++ -c src/rsdl.cpp -o src/rsdl.o

head:
		echo "#include "$(HEAD) > ./src/sdlHeaders.hpp
clean:
	rm -r *.o
