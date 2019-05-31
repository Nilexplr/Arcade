/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Ncurse
*/

#include "Ncurse.hpp"

extern "C" {
	Ncurse *allocatorLib()
	{
		return new Ncurse();
	}
	void deleterLib(Ncurse *ptr)
	{
		delete ptr;
	}
}

Ncurse::Ncurse() : _ch(0), _enemy(), _wall(), _objet(), _character(), _Objmap(), _posMenu()
{
	_posMenu.emplace("posTitle", std::vector<int>({0,20}));
    _posMenu.emplace("posName", std::vector<int>({65, 33}));
    _posMenu.emplace("posBoxname", std::vector<int>({60, 29}));
    _posMenu.emplace("posUndertitle", std::vector<int>({22,43}));
    _posMenu.emplace("sizeBoxname", std::vector<int>({10,40}));
    _posMenu.emplace("posQuestion", std::vector<int>({55, 45}));
    _posMenu.emplace("posBoxGame", std::vector<int>({35, 10}));
    _posMenu.emplace("sizeBoxGame", std::vector<int>({40, 30}));
    _posMenu.emplace("posGame", std::vector<int>({40, 15}));
    _posMenu.emplace("posExit", std::vector<int>({80, 45}));
    _posMenu.emplace("posBoxLib", std::vector<int>({35, 60}));
    _posMenu.emplace("sizeBoxLib", std::vector<int>({40, 30}));
    _posMenu.emplace("posLib", std::vector<int>({40, 65}));
	_posMenu.emplace("posTitleScore", std::vector<int>({70, 70}));
	_posMenu.emplace("posScore", std::vector<int>({75, 70}));
    _posMenu.emplace("posBoxScore", std::vector<int>({73, 67}));
    _posMenu.emplace("sizeBoxScore", std::vector<int>({8, 10}));
	_posMenu.emplace("posMap", std::vector<int>({30, 5}));
}

void Ncurse::openWindow()
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	noecho();
	refresh();
}

void Ncurse::closeWindow()
{
	endwin();
}

Ncurse::~Ncurse()
{
	endwin();
}

void Ncurse::drawObject(std::string name, std::vector<int> pos)
{
	int col, row;
    getmaxyx(stdscr,row,col);
    int x = TRANSCOORD(pos[1], col);
    int y = TRANSCOORD(pos[0], row);
	std::ifstream file("./lib/ncurse/" + name + ".txt");
	std::string string;
	if (file)
		while (getline(file, string)) {
			mvprintw(y, x, string.c_str());
			y++;
		}
	else
		throw std::exception();
}

void Ncurse::drawText(std::vector<int> pos, int fontSize, std::string str, const std::string &couleur)
{
	(void)couleur;
	int col, row;
    getmaxyx(stdscr,row,col);
    int x = TRANSCOORD(pos[1], col);
    int y = TRANSCOORD(pos[0], row);
	mvprintw(y, x, str.c_str());
}

Arcade::Event Ncurse::getEvent()
{
	(_ch = getch());
	if (_ch == 27)
		return Arcade::Event::ECHAP;
	if (_ch == KEY_LEFT)
		return Arcade::Event::KEYLEFT;
	if (_ch == KEY_RIGHT)
		return Arcade::Event::KEYRIGHT;
	if (_ch == KEY_UP)
		return Arcade::Event::KEYUP;
	if (_ch == KEY_DOWN)
		return Arcade::Event::KEYDOWN;
	if (_ch == 10)
		return Arcade::Event::ENTER;
	if (_ch == KEY_BACKSPACE)
		return Arcade::Event::SPACE;
	if (_ch == 122)
		return Arcade::Event::NEXTGAME;
	if (_ch == 97)
		return Arcade::Event::PREVGAME;
	if (_ch == 113)
		return Arcade::Event::PREVLIB;
	if (_ch == 115)
		return Arcade::Event::NEXTLIB;
	if (_ch == 119)
		return Arcade::Event::BUTTON1;
	if (_ch == 120)
		return Arcade::Event::BUTTON2;
	return Arcade::Event::NOTHING;
}

void Ncurse::drawBox(std::vector<int> pos, std::vector<int> size, int type)
{
	int col, row;
	getmaxyx(stdscr,row,col);
	int x = TRANSCOORD(pos[1], col);
	int y = TRANSCOORD(pos[0], row);
	int sizex = TRANSCOORD(size[1], col);
	int sizey = TRANSCOORD(size[0], row);
	(void)type;
	std::string full;
	std::string empty;
	std::string signe = "+";
	full += signe;
	empty += signe;
	for (int i = 1; i < sizex - 1; i++) {
		full += signe;
		empty += " ";
	}
	full += signe;
	empty += signe;
	mvprintw(y, x, full.c_str());
	for (int i = 1; i < sizey - 1; i++)
		mvprintw(y + i, x, empty.c_str());
	mvprintw(y + sizey - 1, x, full.c_str());
}

std::string Ncurse::getString(std::vector<int> pos)
{
	int col, row;
	getmaxyx(stdscr,row,col);
	int x = TRANSCOORD(pos[1], col);
	int y = TRANSCOORD(pos[0], row);
	char buffer[21];
	echo();
	nodelay(stdscr, FALSE);
	mvgetnstr(y, x, buffer, 20);
	noecho();
	nodelay(stdscr, TRUE);
	return std::string(buffer);
}

void Ncurse::updateWindow(void)
{
	refresh();
	usleep(100000);
	clear();
}

void Ncurse::drawCharacter(std::vector<std::vector<int>> charater, std::vector<int> pos)
{
	int col, row;
	getmaxyx(stdscr,row,col);
	int x0 = TRANSCOORD(pos[1], col);
	int y0 = TRANSCOORD(pos[0], row);

	for(int i = 0; i < charater.size(); i++)
	{
		if (i == 0)
			mvprintw(charater.at(i)[0] + y0, charater.at(i)[1] + x0, _character[0].c_str());
		else
			mvprintw(charater.at(i)[0] + y0, charater.at(i)[1] + x0, _character[1].c_str());
	}
}

void Ncurse::loadAsset(const std::string &name)
{
	std::ifstream character("./lib/ncurse/" + name + "/character.txt");
	std::ifstream objet("./lib/ncurse/" + name + "/objet.txt");
	std::ifstream wall("./lib/ncurse/" + name + "/wall.txt");
	std::ifstream enemy("./lib/ncurse/" + name + "/enemy.txt");
	std::string result;
	_character.clear();
	_enemy.clear();
	_objet.clear();
	_wall.clear();
	_Objmap.clear();
	if (character) {
		while(getline(character, result))
			_character.push_back(result);
		_Objmap.emplace("character", _character);
	}
	if (objet) {
		while(getline(objet, result))
			_objet.push_back(result);
		_Objmap.emplace("objet", _objet);
	}
	if (wall) {
		while(getline(wall, result))
			_wall.push_back(result);
		_Objmap.emplace("wall", _wall);
	}
	if (enemy) {
		while(getline(enemy, result))
			_enemy.push_back(result);
		_Objmap.emplace("enemy", _enemy);
	}
}

void Ncurse::drawObjMap(const std::string &type, int id, std::vector<int> pos)
{
	if (_Objmap.find(type) != _Objmap.end())
		mvprintw(pos[0], pos[1], _Objmap[type][id].c_str());
}

void Ncurse::drawMap(std::map<int, std::vector<int>> map, std::vector<int> pos)
{
	int col, row;
    getmaxyx(stdscr,row,col);
    int x0 = TRANSCOORD(pos[1], col);
    int y0 = TRANSCOORD(pos[0], row);
	int x = 0;
	int y = 0;

	for (auto m : map)
	{
		x = 0;
		for (auto i : m.second) {
			if (i == 1)
				drawObjMap("wall", 0, {y + y0, x + x0});
			if (i >= 10)
				drawObjMap("objet", i - 10, {y + y0, x + x0});
			if (i < 0)
				drawObjMap("enemy" ,-i - 1, {y + y0, x + x0});
			x++;
		}
		y++;
	}
}
