/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Ncurse
*/

#ifndef NCURSE_HPP_
#define NCURSE_HPP_

#include "IGraph.hpp"
#include <ncurses.h>
#include "unistd.h"
#include <string>

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs,
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {

	int startx, starty;
	int height, width;
	WIN_BORDER border;
}WIN;

class Ncurse : public Arcade::IGraph {
	public:
		Ncurse();
		~Ncurse();
        void openWindow();
        void closeWindow();
        void updateWindow(void);
        void drawBox(std::vector<int> pos, std::vector<int> size, int type = 0);
		/*!
         * \brief Draw objects
         *
         * Display all the objects present in the game
         *
         * \param object Vector representing the objects' informations
         */
        void drawObject(std::string name, std::vector<int> pos);
        /*!
         * \brief Draw text
         *
         * Display some text
         *
         * \param pos Vector representing the text's position
         * \param fontSize Font size
         * \param str Text to display
         */
        void drawText(std::vector<int> pos, int fontSize, std::string str, const std::string &couleur = "green");
        /*!
         * \brief Get event
         *
         * Catch events occurring while the game loop
         */
        Arcade::Event getEvent();
        std::string getString(std::vector<int> pos);
        void loadAsset(const std::string &name);
		void drawMap(std::map<int, std::vector<int>> map, std::vector<int> pos);
		void drawCharacter(std::vector<std::vector<int>> charater, std::vector<int> pos);
        std::string getName() const {return "ncurse";};
        std::vector<int> getPosMenu(const std::string &id) {return _posMenu[id];};
	protected:
	private:
		int _ch;
		WIN *_window;
        void drawObjMap(const std::string &type, int id, std::vector<int> pos);
        std::vector<std::string> _enemy;
        std::vector<std::string> _wall;
        std::vector<std::string> _objet;
        std::vector<std::string> _character;
        std::map<std::string, std::vector<std::string>> _Objmap;
        std::map<std::string, std::vector<int>> _posMenu;
};

#endif /* !NCURSE_HPP_ */
