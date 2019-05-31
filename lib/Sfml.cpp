/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Sfml
*/

#include "Sfml.hpp"

Sfml::Sfml() :  _window(), _box(), _title(), _event(),
_texture(), _enemy(), _wall(), _objet(), _character(), _posMenu(), _Objmap(), _clock()
{
	sf::RectangleShape box1 = sf::RectangleShape();
	box1.setOutlineThickness(1);
	box1.setOutlineColor(sf::Color::Green);
	box1.setFillColor(sf::Color::Transparent);
	_box.push_back(box1);
	if (!_font.loadFromFile("./lib/sfml/CaviarDreams.ttf"))
		throw std::exception();

	/* POSITION MENU */

	_posMenu.emplace("posTitle", std::vector<int>({0,17}));
    _posMenu.emplace("posName", std::vector<int>({63, 33}));
    _posMenu.emplace("posBoxname", std::vector<int>({60, 29}));
    _posMenu.emplace("posUndertitle", std::vector<int>({33,19}));
    _posMenu.emplace("sizeBoxname", std::vector<int>({10,40}));
    _posMenu.emplace("posQuestion", std::vector<int>({55, 43}));
    _posMenu.emplace("posBoxGame", std::vector<int>({40, 10}));
    _posMenu.emplace("sizeBoxGame", std::vector<int>({40, 30}));
    _posMenu.emplace("posGame", std::vector<int>({45, 15}));
    _posMenu.emplace("posExit", std::vector<int>({85, 47}));
    _posMenu.emplace("posBoxLib", std::vector<int>({40, 60}));
    _posMenu.emplace("sizeBoxLib", std::vector<int>({40, 30}));
    _posMenu.emplace("posLib", std::vector<int>({45, 65}));
	_posMenu.emplace("posTitleScore", std::vector<int>({65, 85}));
	_posMenu.emplace("posScore", std::vector<int>({75, 85}));
    _posMenu.emplace("posBoxScore", std::vector<int>({74, 84}));
    _posMenu.emplace("sizeBoxScore", std::vector<int>({5, 10}));
    _posMenu.emplace("posMap", std::vector<int>({40, 3}));
}

Sfml::~Sfml()
{
}

void Sfml::openWindow()
{
	_window.create(sf::VideoMode(1920,1200), "Arcade");
}

void Sfml::closeWindow()
{
	_window.close();
}

void Sfml::drawBox(std::vector<int> pos, std::vector<int> size, int type)
{
	sf::RectangleShape box = sf::RectangleShape(_box[type]);
	box.setPosition((float)TRANSX(pos[1], (int)_window.getSize().x), (float)TRANSY(pos[0], (int)_window.getSize().y));
	box.setSize({(float)TRANSX(size[1], (int)_window.getSize().x), (float)TRANSY(size[0], (int)_window.getSize().y)});
	_window.draw(box);
}

void Sfml::drawObject(std::string name, std::vector<int> pos)
{
	(void)pos;
	(void)name;
	sf::Sprite sprite;
	sf::Texture texture;
	if(texture.loadFromFile("./lib/sfml/" + name + ".png")) {
		sprite.setTexture(texture);
		sprite.setPosition((float)TRANSCOORD(pos[1], (int)_window.getSize().x), (float)TRANSCOORD(pos[0], (int)_window.getSize().y));
		_window.draw(sprite);
	}
	else
		throw std::exception();
}
  
void Sfml::drawText(std::vector<int> pos, int fontSize, std::string str,  const std::string &couleur)
{
	static sf::Text *text = new sf::Text();
	sf::Color color(9, 106, 9);

    text->setFont(_font);
    text->setString(str);
    text->setCharacterSize(fontSize);
	if (couleur =="green")
	    text->setFillColor(sf::Color::Green);
	if (couleur == "selected")
		text->setFillColor(color);
	if (couleur =="yellow")
	    text->setFillColor(sf::Color::Yellow);
    text->setPosition((float)TRANSCOORD(pos[1], (int)_window.getSize().x), (float)TRANSCOORD(pos[0], (int)_window.getSize().y));
	_window.draw(*text);
}

Arcade::Event Sfml::getEvent()
{
	sf::Event event;

	if (_window.pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
				return Arcade::Event::ECHAP;
			if (event.key.code == sf::Keyboard::Up)
				return Arcade::Event::KEYUP;
			if (event.key.code == sf::Keyboard::Right)
				return Arcade::Event::KEYRIGHT;
			if (event.key.code == sf::Keyboard::Left)
				return Arcade::Event::KEYLEFT;
			if (event.key.code == sf::Keyboard::Down)
				return Arcade::Event::KEYDOWN;
			if (event.key.code == sf::Keyboard::Enter)
				return Arcade::Event::ENTER;
			if (event.key.code == sf::Keyboard::Space)
				return Arcade::Event::SPACE;
			if (event.key.code == sf::Keyboard::A)
				return Arcade::Event::PREVGAME;
			if (event.key.code == sf::Keyboard::Z)
				return Arcade::Event::NEXTGAME;
			if (event.key.code == sf::Keyboard::Q)
				return Arcade::Event::PREVLIB;
			if (event.key.code == sf::Keyboard::S)
				return Arcade::Event::NEXTLIB;
			if (event.key.code == sf::Keyboard::W)
				return Arcade::Event::BUTTON1;
			if (event.key.code == sf::Keyboard::X)
				return Arcade::Event::BUTTON2;
		}
		if (event.type == sf::Event::Closed)
			return Arcade::Event::CLOSE;
		return Arcade::Event::NOTHING;
	}
	return Arcade::Event::NOTHING;
}

std::string Sfml::getString(std::vector<int> pos)
{
	(void)pos;
	std::string str = "";
	sf::Event event;

	while (1) {
		_window.display();
		_window.waitEvent(event);
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128)
    		{
    		    str += static_cast<char>(event.text.unicode);
    		    drawText(pos, 30, str);
    		}
		}
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Enter && str != "")
				break;
	}
	return str;
}

void Sfml::drawCharacter(std::vector<std::vector<int>> charater, std::vector<int> pos)
{
	float x0 = TRANSCOORD(pos[1], (int)_window.getSize().x);
	float y0 = TRANSCOORD(pos[0], (int)_window.getSize().y);

	for(auto x : charater) {
		sf::Sprite sprite(_character.front());
		sprite.setPosition({x[1] * 19 + x0, x[0] * 19 + y0});
		_window.draw(sprite);
	}
}

void Sfml::updateWindow()
{
	sf::Time time = _clock.getElapsedTime();
	_window.display();
	float elapsed = time.asMicroseconds();
	while (elapsed < 100000)
		elapsed = _clock.getElapsedTime().asMicroseconds();
	_clock.restart();
	_window.clear();
}

void Sfml::loadAsset(const std::string &name)
{
	_character.clear();
	_enemy.clear();
	_objet.clear();
	_wall.clear();
	_Objmap.clear();
	_texture.clear();
	sf::Texture texture;
	sf::Sprite sprite;
	int i = 0;
	while (std::ifstream("./lib/sfml/" + name + "/character" + std::to_string(i) + ".png")) {
		texture.loadFromFile("./lib/sfml/" + name + "/character" + std::to_string(i) + ".png");
		_texture.push_back(sf::Texture(texture));
		sprite.setTexture(_texture.back());
		sprite.setScale(0.5f, 0.5f);
		_character.push_back(sf::Sprite(sprite));
		i++;
	}
	i = 0;
	if (_character.size() > 0)
		_Objmap.emplace("character", _character);
	while (std::ifstream("./lib/sfml/" + name + "/objet" + std::to_string(i) + ".png")) {
		texture.loadFromFile("./lib/sfml/" + name + "/objet" + std::to_string(i) + ".png");
		_texture.push_back(sf::Texture(texture));
		sprite.setTexture(_texture.back());
		sprite.setScale(0.5f, 0.5f);
		_objet.push_back(sf::Sprite(sprite));
		i++;
	}
	i = 0;
	if (_objet.size() > 0)
		_Objmap.emplace("objet", _objet);
	while (std::ifstream("./lib/sfml/" + name + "/wall" + std::to_string(i) + ".png")) {
		texture.loadFromFile("./lib/sfml/" + name + "/wall" + std::to_string(i) + ".png");
		_texture.push_back(sf::Texture(texture));
		sprite.setTexture(_texture.back());
		sprite.setScale(0.5f, 0.5f);
		_wall.push_back(sf::Sprite(sprite));
		i++;
	}
	i = 0;
	if (_wall.size() > 0)
		_Objmap.emplace("wall", _wall);
	while (std::ifstream("./lib/sfml/" + name + "/enemy" + std::to_string(i) + ".png")) {
		texture.loadFromFile("./lib/sfml/" + name + "/enemy" + std::to_string(i) + ".png");
		_texture.push_back(sf::Texture(texture));
		sprite.setTexture(_texture.back());
		sprite.setScale(0.5f, 0.5f);
		_enemy.push_back(sf::Sprite(sprite));
		i++;
	}
	if (_enemy.size() > 0)
		_Objmap.emplace("enemy", _enemy);
}

void Sfml::drawObjMap(const std::string &type, int id, std::vector<int> pos)
{
	if (_Objmap.find(type) != _Objmap.end()) {
		sf::Sprite sprite(_Objmap[type][id]);
		sprite.setPosition({(float)pos[1], (float)pos[0]});
		_window.draw(sprite);
	}
}

void Sfml::drawMap(std::map<int, std::vector<int>> map, std::vector<int> pos)
{
	float x0 = TRANSCOORD(pos[1], (int)_window.getSize().x);
	float y0 = TRANSCOORD(pos[0], (int)_window.getSize().y);
	int x = 0;
	int y = 0;

	for (auto m : map)
	{
		x = 0;
		for (auto i : m.second) {
			if (i == 1)
				drawObjMap("wall", 0, {y * 19 + (int)y0,x * 19 + (int)x0});
			if (i >= 10)
				drawObjMap("objet", i - 10, {y * 19 + (int)y0, x * 19 + (int)x0});
			if (i < 0)
				drawObjMap("enemy" ,-i - 1, {y * 19 + (int)y0, x * 19 + (int)x0});
			x++;
		}
		y++;
	}
}

extern "C"
{
	Sfml *allocatorLib()
	{
		return new Sfml();
	}

	void deleterLib(Sfml *ptr)
	{
		delete ptr;
	}
}
