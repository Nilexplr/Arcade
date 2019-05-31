/*
** EPITECH PROJECT, 2019
** Tech_2
** File description:
** SolarFox
*/

#include "SolarFox.hpp"

SolarFox::SolarFox() : _gameOver(false), _map(), _score(0)
, _charact(), _pos(), _direction(0), _lvl(1), _posMissil(), _dirMissil(),
_EnemyPos()
{
	setMap("resources/SolarFox/map.txt");
	_charact.push_back({13, 35});
	std::srand(std::time(nullptr));
	setEnemy();
}

SolarFox::~SolarFox()
{
}

void SolarFox::setEnemy()
{
	int x = 1;
	int y = 1;
	for (int i = 0; i < _lvl; i++) {
		x = 1;
		y = 1;
		int counter = std::rand() % 4;
		if (counter == 0)
			x += (std::rand() % 60 + 4);
		if (counter == 1) {
			x += (std::rand() % 60 + 4);
			y = 23;
		}
		if (counter == 2) {
			y += (std::rand() % 17 + 3);
		}
		if (counter == 3) {
			x = 67;
			y += (std::rand() % 17 + 3);
		}
	if (_map[y][x] != -1)
		_map[y][x] = -1;
	_EnemyPos.push_back({y,x});
	}
}

void SolarFox::clearProjMap()
{
	int x = 0;
	int y = 0;
	for (auto m : _map) {
		x = 0;
		for (auto z : m.second) {
			if (z == -2)
				_map[y][x] = _realmap[y][x] == 1 ? 1: 0;
			x++;
		}
		y++;
	}
}

void SolarFox::EnemyShoot()
{
	for (auto x : _EnemyPos) {
		if (_posMissil.size() > _EnemyPos.size() + 2)
			continue;
		if (x.front() == 1) {
			_posMissil.push_back({x.front() + 1, x.back()});
			_dirMissil.push_back({1, 0});
		}
		if (x.front() == 23) {
			_posMissil.push_back({x.front() - 1, x.back()});
			_dirMissil.push_back({-1, 0});
		}
		if (x.back() == 1) {
			_posMissil.push_back({x.front(), x.back() + 1});
			_dirMissil.push_back({0, 1});
		}
		if (x.back() == 67) {
			_posMissil.push_back({x.front(), x.back() - 1});
			_dirMissil.push_back({0, -1});
		}
	}
}

void SolarFox::updateShoot()
{
	clearProjMap();
	int i = 0;
	while (i < (int)_posMissil.size()) {
		_posMissil[i][0] += _dirMissil[i][0]; 
		_posMissil[i][1] += _dirMissil[i][1];
		if (_posMissil[i][0]  > 23 || _posMissil[i][0]  == 0 || _posMissil[i][1]  == 1 || _posMissil[i][1]  >= 68) {
			_posMissil.erase(_posMissil.begin() + i);
			_dirMissil.erase(_dirMissil.begin() + i);
			i--;
		}
		else
			_map[_posMissil[i][0]][_posMissil[i][1]] = -2;
		i++;
	}
}

void SolarFox::updateEnemy()
{
	for (auto x : _EnemyPos)
			_map[x[0]][x[1]] = -1;
}

void SolarFox::updateGame(Arcade::Event event)
{
	EnemyShoot();
	updateShoot();
	updateEnemy();
	if((event == Arcade::Event::KEYRIGHT || _direction == 1) && _direction != 4) {
		_charact.front().back() += 1;
		_direction = 1;
	}
	if((event == Arcade::Event::KEYDOWN || _direction == 2) && _direction != 3) {
		_charact.front().front() += 1;
		_direction = 2;
	}
	if((event == Arcade::Event::KEYUP || _direction == 3) && _direction != 2) {
		_charact.front().front() -= 1;
		_direction = 3;
	}
	if((event == Arcade::Event::KEYLEFT || _direction == 4) && _direction != 1) {
		_charact.front().back() -= 1;
		_direction = 4;
	}
	int y = _charact.front().front();
	int x = _charact.front().back();
	if (_map[y][x] < 10 && _map[y][x] != 0)
		_gameOver = true;
	if (_map[y][x] >= 10){
		_map[y][x] = 0;
		_score += 10;
	}
	if (isWin()) {
		resetGame();
		_lvl++;
	}
}


void SolarFox::setCharacterPos(std::vector<std::vector<int>> character)
{
	(void)character;
}

void SolarFox::setMap(const std::string path)
{
	std::string m;
	std::ifstream level(path);

	if (level)
	{
	 	for (int i = 0; getline(level, m); i++)
		{
			std::vector<int> tmp;
			for (auto x: m) {
				if (x - 48 >5)
					tmp.push_back(x - 48 + 4);
				else
					tmp.push_back(x - 48);
			}
 			_map.emplace(i, tmp);
			_realmap.emplace(i, tmp);
		}

	}
	else
		throw std::exception();
}
 
void SolarFox::resetGame()
{
	_map.clear();
	setMap("resources/SolarFox/map.txt");
	_charact.clear();
	_charact.push_back({13, 35});
	_direction = 0;
	_posMissil.clear();
	_dirMissil.clear();
	_EnemyPos.clear();
	setEnemy();
	if (_gameOver == true) {
		_gameOver = false;
		_score = 0;
	}
}

bool SolarFox::isWin()
{
	for (auto m : _map)
		for (auto x : m.second)
			if (x >= 10)
				return false;
	return true;
}

extern "C"
{
	SolarFox *allocatorGame()
	{
		return new SolarFox();
	}

	void deleterGame(SolarFox *ptr)
	{
		delete ptr;
	}
}