/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP_
#define SOLARFOX_HPP_
#include "IGame.hpp"

class SolarFox : public Arcade::IGame {
	public:
		SolarFox();
		~SolarFox();
		void setCharacterPos(std::vector<std::vector<int>> character);
        void setMap(const std::string path);
        std::vector<std::vector<int>> getCharacter() {return _charact;};
        std::map<int, std::vector<int>> &getMap() {return _map;};
        int getScore() const {return _score;};
        void updateGame(Arcade::Event event);
        bool gameOver() const {return _gameOver;};
		std::string getName() const {return "SolarFox";};
        void resetGame();
	protected:
	private:
		bool _gameOver;
		std::map<int, std::vector<int>> _map;
		std::map<int, std::vector<int>> _realmap;
		int _score;
		std::vector<std::vector<int>> _charact;
		std::vector<int> _pos;
		int _direction;
		int _lvl;
		bool isWin();
		void clearProjMap();
		void setEnemy();
		void EnemyShoot();
		void updateShoot();
		void updateEnemy();
		std::vector<std::vector<int>> _posMissil;
		std::vector<std::vector<int>> _dirMissil;
		std::vector<std::vector<int>> _EnemyPos;
};

#endif /* !SOLARFOX_HPP_ */
