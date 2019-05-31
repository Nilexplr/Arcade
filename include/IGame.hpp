/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Games interface
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include <vector>
#include <string>
#include <map>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "utility.hpp"
#include <ctime>

namespace Arcade {
class IGame {
    public:
        virtual ~IGame() = default;
        /*!
         * \brief Set main charater's position
         *
         * Set main character's position
         *
         * \param pos Vector representing the main character position
         */
        virtual void setCharacterPos(std::vector<std::vector<int>> character) = 0;
        /*!
         * \brief Set boxes settings
         *
         * Set boxes' positions
         *
         * \param pos Vector representing the boxes' positions
         */
        virtual void setMap(const std::string path) = 0;
        virtual std::vector<std::vector<int>> getCharacter() = 0;
        virtual std::map<int, std::vector<int>> &getMap() = 0;
        virtual int getScore() const = 0;
        virtual void updateGame(Arcade::Event event) = 0;
        virtual bool gameOver() const = 0;
		virtual void resetGame() = 0;
        virtual std::string getName() const = 0;
};
}
#endif /* !IGAME_HPP_ */
