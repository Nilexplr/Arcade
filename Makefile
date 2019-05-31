##
## EPITECH PROJECT, 2019
## OOP_arcade_2018
## File description:
## Makefile
##

SRC_LIBCACA= ./lib/Libcaca.cpp

SRC_NCURSE= ./lib/Ncurse.cpp

OBJ_NCURSE= $(SRC_NCURSE:.cpp=.o)

SRC_SFML= ./lib/Sfml.cpp

OBJ_SFML= $(SRC_SFML:.cpp=.o)

SRC_SNAKE= ./games/Nibbler.cpp

OBJ_SNAKE= $(SRC_SNAKE:.cpp=.o)

SRC_SOLARFOX= ./games/SolarFox.cpp

OBJ_SOLARFOX= $(SRC_SOLARFOX:.cpp=.o)

SRC_CORE= 	./src/Core.cpp \
			./src/Loader.cpp \
			./src/Menu.cpp

OBJ_CORE= $(SRC_CORE:.cpp=.o)

MAIN= ./src/main.cpp

CXXFLAGS	=	-I./include -Wall -Wextra -Werror -ldl -g3

UT_SRC=

UT  =   unit_tests

NAME= arcade

all: core games graphicals

core: $(OBJ_CORE) $(MAIN:.cpp=.o)
		g++ $(OBJ_CORE) $(MAIN:.cpp=.o) -o $(NAME) $(CXXFLAGS)

graphicals: $(OBJ_SFML)
			g++ $(SRC_SFML) -o lib/lib_arcade_sfml.so -shared -fPIC -lsfml-graphics -lsfml-window -lsfml-system -I./include
			g++ $(SRC_NCURSE) -o lib/lib_arcade_ncurse.so -shared -fPIC -lncurses -I./include
			g++ $(SRC_LIBCACA) -o lib/lib_arcade_libcaca.so -shared -fPIC -lcaca -I./include

games: $(OBJ_SNAKE) $(OBJ_SOLARFOX)
			g++ $(SRC_SNAKE) -o games/lib_arcade_nibbler.so -shared -fPIC -I./include
			g++ $(SRC_SOLARFOX) -o games/lib_arcade_solarfox.so -shared -fPIC -I./include

tests_run:
		g++ -o $(UT) $(UT_SRC) $(INCLUDE) $(SRC) $(CXXFLAGS) $(LDFLAGS)
		./$(UT) --always-succeed

clean:
		rm -f $(OBJ_CORE) $(OBJ_NCURSE) $(OBJ_SFML) $(OBJ_SOLARFOX) $(OBJ_SNAKE)


fclean: clean
		rm -f lib/lib_arcade_sfml.so games/lib_arcade_nibbler.so lib/lib_arcade_ncurse.so games/lib_arcade_solarfox.so src/main.o $(NAME) $(UT)


re:	fclean all

.PHONY: clean fclean re all
