/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Graphical interface
*/

#ifndef IGRAPH_HPP_
#define IGRAPH_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <unistd.h>
#include <fstream>
#include "utility.hpp"


#define TRANSCOORD(x, y) (x * y / 100)

namespace Arcade {
    /*!
     * \class IGraph
     * \brief Graphical interface
     */
    class IGraph {
        public:
            virtual ~IGraph() = default;
            virtual void openWindow() = 0;
            virtual void closeWindow() = 0;
            /*!
             * \brief Draw main character
             *
             * Used to display the main character on the screen
             *
             * \param pos Vector representing the player's position
             */
            virtual void drawCharacter(std::vector<std::vector<int>> charater, std::vector<int> pos) = 0;
            /*!
             * \brief Draw box
             *
             * Display main menu boxes
             *
             * \param pos Vector representing the boxes' positions
             */
            virtual void drawBox(std::vector<int> pos, std::vector<int> size, int type = 0) = 0;
            /*!
             * \brief Update window
             *
             * Update the game window display
             */
            virtual void updateWindow() = 0;
            /*!
             * \brief Draw objects
             *
             * Display all the objects present in the game
             *
             * \param object Vector representing the objects' informations
             */
            virtual void drawObject(std::string name, std::vector<int> pos) = 0;
            /*!
             * \brief Draw text
             *
             * Display some text
             *
             * \param pos Vector representing the text's position
             * \param fontSize Font size
             * \param str Text to display
             */
            virtual void drawText(std::vector<int> pos, int fontSize, std::string str, const std::string &couleur = "green") = 0;
            /*!
    		 * \brief Draw map
             *
             * Display the map of the game
             *
             * \param object Vector representing the objects' informations
             */
            virtual Arcade::Event getEvent() = 0;
            virtual std::string getString(std::vector<int> pos) = 0;
            virtual void loadAsset(const std::string &name) = 0;
    		virtual void drawMap(std::map<int, std::vector<int>> map, std::vector<int> pos) = 0;
            virtual std::string getName() const = 0;
	        virtual std::vector<int> getPosMenu(const std::string &id) = 0;
    	};
}
#endif /* !IGRAPH_HPP_ */
