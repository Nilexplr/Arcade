/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <string>
#include <vector>
#include <memory>
#include "IGraph.hpp"

class Menu {
	public:
		Menu();
		~Menu();
                void setName(char c) {_name += c;};
                std::string getName() const {return _name;};
                size_t getScore(int selected, int id) const {return _score[selected][id];};
                std::string getGame(int id) const {return _games[id];};
                bool getValid() const {return _validname;};
                void askName(std::shared_ptr<Arcade::IGraph> lib);
                void loadGameName(std::vector<std::string> gameName) {_games = gameName;};
                void loadLibName(std::vector<std::string> libName) {_lib = libName;};
                void handlingMenu(std::shared_ptr<Arcade::IGraph> lib);
                int update(Arcade::Event event);
                void drawHUD(std::shared_ptr<Arcade::IGraph> lib, const std::string &name, int score);
	private:
                std::string _name;
                std::vector<std::vector<size_t>> _score;
                std::vector<std::string> _games;
                std::vector<std::string> _lib;
                int selected_bloc;
                bool _validname;

};

#endif /* !MENU_HPP_ */
