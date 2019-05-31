/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** __DESCRIPTION__
*/

#include "Libcaca.hpp"

extern "C" {
	Libcaca *allocatorLib()
	{
		return new Libcaca();
	}
	void deleterLib(Libcaca *ptr)
	{
		delete ptr;
	}
}

Libcaca::Libcaca() : _enemy(), _wall(), _objet(), _character(), _Objmap(), _posMenu()
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

void Libcaca::openWindow()
{
	_cv = caca_create_canvas(250, 60);
	_window = caca_create_display(_cv);
	caca_set_color_ansi(_cv, CACA_CONIO_GREEN, CACA_BLACK);
}

void Libcaca::closeWindow()
{
	 caca_free_display(_window);
}

Libcaca::~Libcaca()
{
}

void Libcaca::drawObject(std::string name, std::vector<int> pos)
{
	int col = caca_get_canvas_width(_cv);
	int row = caca_get_canvas_height(_cv);
    int x = TRANSCOORD(pos[1], col);
    int y = TRANSCOORD(pos[0], row);
	std::ifstream file("./lib/libcaca/" + name + ".txt");
	std::string string;
	if (file)
		while (getline(file, string)) {
			caca_put_str(_cv, x, y, string.c_str());
			y++;
		}
	else
		throw std::exception();
}

void Libcaca::drawText(std::vector<int> pos, int fontSize, std::string str, const std::string &couleur)
{
	if (couleur == "green")
		caca_set_color_ansi(_cv, CACA_CONIO_LIGHTGREEN, CACA_BLACK);
	if (couleur == "selected")
		caca_set_color_ansi(_cv, CACA_CONIO_GREEN, CACA_BLACK);
	if (couleur =="yellow")
		caca_set_color_ansi(_cv, CACA_CONIO_YELLOW, CACA_BLACK);
	int col = caca_get_canvas_width(_cv);
	int row = caca_get_canvas_height(_cv);;
    int x = TRANSCOORD(pos[1], col);
    int y = TRANSCOORD(pos[0], row);
	caca_put_str(_cv, x, y, str.c_str());
	caca_set_color_ansi(_cv, CACA_CONIO_GREEN, CACA_BLACK);
}

Arcade::Event Libcaca::getEvent()
{
	if (caca_get_event(_window, CACA_EVENT_KEY_PRESS, &_ch, 0) == 1) {
		switch (caca_get_event_key_ch(&_ch)) {
			case CACA_KEY_ESCAPE :
				return Arcade::Event::ECHAP;
			case CACA_KEY_LEFT :
				return Arcade::Event::KEYLEFT;
			case CACA_KEY_RIGHT :
				return Arcade::Event::KEYRIGHT;
			case CACA_KEY_UP :
				return Arcade::Event::KEYUP;
			case CACA_KEY_DOWN :
				return Arcade::Event::KEYDOWN;
			case CACA_KEY_RETURN :
				return Arcade::Event::ENTER;
			case CACA_KEY_BACKSPACE :
				return Arcade::Event::SPACE;
			case 'z' :
				return Arcade::Event::NEXTGAME;
			case 'a':
				return Arcade::Event::PREVGAME;
			case 'q':
				return Arcade::Event::PREVLIB;
			case 's':
				return Arcade::Event::NEXTLIB;
			case 'w':
				return Arcade::Event::BUTTON1;
			case 'x':
				return Arcade::Event::BUTTON2;
		}

	}

	return Arcade::Event::NOTHING;
}

void Libcaca::drawBox(std::vector<int> pos, std::vector<int> size, int type)
{
	int col = caca_get_canvas_width(_cv);
	int row = caca_get_canvas_height(_cv);;
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
	caca_put_str(_cv, x, y, full.c_str());
	for (int i = 1; i < sizey - 1; i++)
		caca_put_str(_cv, x, y + i, empty.c_str());
	caca_put_str(_cv, x, y + sizey - 1, full.c_str());
}

std::string Libcaca::getString(std::vector<int> pos)
{
	int col = caca_get_canvas_width(_cv);
	int row = caca_get_canvas_height(_cv);
	int x = TRANSCOORD(pos[1], col);
	int y = TRANSCOORD(pos[0], row);
	std::string str = "";
	int event;

	caca_refresh_display(_window);
	while (1) {
		if (caca_get_event(_window, CACA_EVENT_KEY_PRESS, &_ch, 0) == 1)
		{
			event = caca_get_event_key_ch(&_ch);
			if (event != CACA_KEY_RETURN)
				str += static_cast<char>(event);
			drawText(pos, 30, str);
			caca_refresh_display(_window);
		}
		if (event == CACA_KEY_RETURN && str != "")
				break;
	}
	return str;
}

void Libcaca::updateWindow(void)
{
	caca_refresh_display(_window);
	usleep(100000);
	caca_clear_canvas(_cv);
}

void Libcaca::drawCharacter(std::vector<std::vector<int>> charater, std::vector<int> pos)
{
	int col = caca_get_canvas_width(_cv);
	int row = caca_get_canvas_height(_cv);
	int x0 = TRANSCOORD(pos[1], col);
	int y0 = TRANSCOORD(pos[0], row);

	for(int i = 0; i < charater.size(); i++)
	{
		if (i == 0)
			caca_put_str(_cv, charater.at(i)[1] + x0, charater.at(i)[0] + y0, _character[0].c_str());
		else
			caca_put_str(_cv, charater.at(i)[1] + x0, charater.at(i)[0] + y0, _character[1].c_str());
	}
}

void Libcaca::loadAsset(const std::string &name)
{
	std::ifstream character("./lib/libcaca/" + name + "/character.txt");
	std::ifstream objet("./lib/libcaca/" + name + "/objet.txt");
	std::ifstream wall("./lib/libcaca/" + name + "/wall.txt");
	std::ifstream enemy("./lib/libcaca/" + name + "/enemy.txt");
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

void Libcaca::drawObjMap(const std::string &type, int id, std::vector<int> pos)
{
	if (_Objmap.find(type) != _Objmap.end())
		caca_put_str(_cv, pos[1], pos[0], _Objmap[type][id].c_str());
}

void Libcaca::drawMap(std::map<int, std::vector<int>> map, std::vector<int> pos)
{
	int col = caca_get_canvas_width(_cv);
	int row = caca_get_canvas_height(_cv);
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
