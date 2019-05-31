/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_
#include "IGame.hpp"
#include "IGraph.hpp"
#include "Menu.hpp"
#include <iostream>
#include <algorithm>
#include "Loader.hpp"
#include <dirent.h>
#include <string>

namespace Arcade {
	class Core {
		public:
			Core(const std::string &path);
			~Core();
			void mainLoop();
			void menuLoop();
			void gameLoop();
			void changeGame(int counter);
			void changeGraphical(int counter);
			void loadGraphical();
			void loadGame();
			void analyseEvent();
			std::vector<std::string> getGameName() const;
			std::vector<std::string> getLibName() const;
		private:
			Loader _loader;
			Menu _objMenu;
			std::vector<void *> _lib;
			size_t _actualGame;
			size_t _actualGraph;
			std::vector<std::shared_ptr<IGame>> _game;
			std::vector<std::shared_ptr<IGraph>> _graph;
			bool _menu;
			bool _application;
			Arcade::Event _event;
			bool _counterMenu;
			std::string _nameactual;
	};
}
#endif /* !CORE_HPP_ */
