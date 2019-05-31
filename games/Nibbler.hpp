/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** __DESCRIPTION__
*/

#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "IGraph.hpp"
#include "IGame.hpp"

class Nibbler : public Arcade::IGame {
	public:
		Nibbler();
		~Nibbler();
        /*!
         * \brief Set main charater's position
         *
         * Set main character's position
         *
         * \param pos Vector representing the main character position
         */
        void setCharacterPos(std::vector<std::vector<int>> character) {_snake = character;};
        /*!
         * \brief Set boxes settings
         *
         * Set boxes' positions
         *
         * \param pos Vector representing the boxes' positions
         */
        void setBox(std::vector<int> pos) {(void)pos;};
        /*!
         * \brief Set objects' settings
         *
         * Set objects' settings
         *
         * \param obj Vector representing the objects
         */
        void setObject(std::vector<int> obj) {(void)obj;};
        /*!
         * \brief Set score
         *
         * Set and update scores
         *
         * \param score Score to be set
         */
        std::vector<std::vector<int>> getCharacter() {return _snake;};
        void setMap(const std::string path);
        std::map<int, std::vector<int>> &getMap() {return (_map);};
        int getScore() const {return (_score);};
        void updateGame(Arcade::Event event);
        bool gameOver() const {return (_gameOver);};
		void resetGame();
        std::string getName() const {return "Nibbler";};
	private:
		bool _gameOver;
		std::vector<std::vector<int>> _snake;
		int _direction;
		std::map<int, std::vector<int>> _map;
		int _score;
		const std::vector<int> _pos;
		std::vector<std::vector<int>> cells;
};

#endif /* !NIBBLER_HPP */
