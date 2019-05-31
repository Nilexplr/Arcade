/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** __DESCRIPTION__
*/

#include "Nibbler.hpp"

extern "C" {
	Nibbler *allocatorGame()
	{
		return new Nibbler();
	}
	void deleterGame(Nibbler *ptr)
	{
		delete ptr;
	}
}

Nibbler::Nibbler()
{
	std::vector<int> p = {10, 10};
	std::vector<int> p1 = {10, 11};
	std::vector<int> p2 = {10, 12};
	std::vector<int> p3 = {10, 13};

	_gameOver = false;
	_snake = std::vector<std::vector<int>>();
	_snake.push_back(p);
	_snake.push_back(p1);
	_snake.push_back(p2);
	_snake.push_back(p3);
	_direction = 0;
	setMap("resources/Nibbler/level_1");
	int y = std::rand()%(_map.size() - 2) + 1;
	int x = std::rand()%(_map[0].size() - 2) + 1;
	_map[y][x] = 10;
	_score = 0;
}

Nibbler::~Nibbler()
{
}


void Nibbler::updateGame(Arcade::Event event)
{
	if (_map[_snake.front().front()][_snake.front().back()] == 10) {
		_snake.push_back({0, 0});
		_map[_snake.front().front()][_snake.front().back()] = 0;
		int y = std::rand()%(_map.size() - 2) + 1;
		int x = std::rand()%(_map[0].size() - 2) + 1;
		_map[y][x] = 10;
		_score += 10;
	}
	for(unsigned int i = 1; i < _snake.size(); i++)
	{
		if (_snake.at(i)[0] == _snake.front().front() && _snake.at(i)[1] == _snake.front().back()) {
			_gameOver = true;
			return;
		}
	}
	if (_map[_snake.front().front()][_snake.front().back()] == 1) {
		_gameOver = true;
		return;
	}
	if (_direction != 0)
		for(int i = _snake.size() - 2; i >= 0; i--)
			_snake.at(i + 1) = _snake.at(i);
	if((event == Arcade::Event::KEYRIGHT || _direction == 1) && _direction != 4) {
		_snake.front().back() += 1;
		_direction = 1;
	}
	if((event == Arcade::Event::KEYDOWN || _direction == 2) && _direction != 3) {
		_snake.front().front() += 1;
		_direction = 2;
	}
	if((event == Arcade::Event::KEYUP || _direction == 3) && _direction != 2) {
		_snake.front().front() -= 1;
		_direction = 3;
	}
	if((event == Arcade::Event::KEYLEFT || _direction == 4) && _direction != 1) {
		_snake.front().back() -= 1;
		_direction = 4;
	}
	setCharacterPos(_snake);
}

void Nibbler::setMap(const std::string path)
{
	std::string m;
	std::ifstream level(path);

	if (level)
	{
	 	for (int i = 0; getline(level, m); i++)
		{
			std::vector<int> tmp;
			for (auto x: m) {
				tmp.push_back(x - 48);
			}
 			_map.emplace(i, tmp);
		}

	}
	else
		throw std::exception();
}

void Nibbler::resetGame()
{
	std::vector<int> p = {10, 10};
	std::vector<int> p1 = {10, 11};
	std::vector<int> p2 = {10, 12};
	std::vector<int> p3 = {10, 13};

	_map.clear();
	_snake.clear();
	_gameOver = false;
	_snake = std::vector<std::vector<int>>();
	_snake.push_back(p);
	_snake.push_back(p1);
	_snake.push_back(p2);
	_snake.push_back(p3);
	_direction = 0;
	setMap("resources/Nibbler/level_1");
	int y = std::rand()%(_map.size() - 2) + 1;
	int x = std::rand()%(_map[0].size() - 2) + 1;
	_map[y][x] = 10;
	_score = 0;
}
