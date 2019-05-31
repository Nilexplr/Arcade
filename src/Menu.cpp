/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu() : _name(), _score(), _games(), selected_bloc(0), _validname(false)
{
    
}

Menu::~Menu()
{
}

void Menu::drawHUD(std::shared_ptr<Arcade::IGraph> lib, const std::string &name, int score)
{
    lib->drawObject(name, lib->getPosMenu("posTitle"));
    lib->drawText(lib->getPosMenu("posTitleScore"), 40,"Score");
    lib->drawBox(lib->getPosMenu("posBoxScore"), lib->getPosMenu("sizeBoxScore"));
    lib->drawText(lib->getPosMenu("posScore"), 20, std::to_string(score), "yellow");
}

void Menu::askName(std::shared_ptr<Arcade::IGraph> lib)
{
    lib->drawText(lib->getPosMenu("posQuestion"), 30, "ENTER YOUR NAME");
    lib->drawBox(lib->getPosMenu("posBoxname"), lib->getPosMenu("sizeBoxname"));
    _name = lib->getString(lib->getPosMenu("posName"));
    if (_name != "")
        _validname = true;
}

void Menu::handlingMenu(std::shared_ptr<Arcade::IGraph> lib)
{
    lib->drawBox(lib->getPosMenu("posBoxGame"), lib->getPosMenu("sizeBoxGame"));
    lib->drawBox(lib->getPosMenu("posBoxLib"), lib->getPosMenu("sizeBoxLib"));
    int y = 0;
    for (int i = 0; i < (int)_games.size(); i++) {
        if (i != selected_bloc)
            lib->drawText({lib->getPosMenu("posGame")[0] + y, lib->getPosMenu("posGame")[1]}, 20, _games[i], "selected");
        y += 4;
    }
    y = 0;
    for (int i = 0; i < (int)_lib.size(); i++) {
        if (i != selected_bloc - (int)_games.size() - 1)
            lib->drawText({lib->getPosMenu("posLib")[0] + y, lib->getPosMenu("posLib")[1]}, 20, _lib[i], "selected");
        else if (selected_bloc <= (int)_games.size())
            lib->drawText({lib->getPosMenu("posLib")[0] + y, lib->getPosMenu("posLib")[1]}, 20, _lib[i], "selected");
        y += 4;
    }
    if (selected_bloc < (int)_games.size()) {
        lib->drawText(lib->getPosMenu("posExit"), 30, "EXIT", "selected");
        lib->drawText({lib->getPosMenu("posGame")[0] + 4 * selected_bloc, lib->getPosMenu("posGame")[1]}, 20, _games[selected_bloc]);
    } else if (selected_bloc > (int)_games.size()) {
        lib->drawText(lib->getPosMenu("posExit"), 30, "EXIT", "selected");
        lib->drawText({lib->getPosMenu("posLib")[0] + 4 * (selected_bloc - ((int)_games.size() + 1)), lib->getPosMenu("posLib")[1]}, 20, _lib[selected_bloc - ((int)_games.size() + 1)]);
    }
    else
        lib->drawText(lib->getPosMenu("posExit"), 30, "EXIT");
}

int Menu::update(Arcade::Event event)
{
    if (event == Arcade::KEYUP)
        selected_bloc -= selected_bloc != 0 && selected_bloc != (int)_games.size() + 1 ? 1 : 0;
    if (event == Arcade::KEYDOWN) {
        selected_bloc += selected_bloc != (int)_games.size() ? 1 : 0;
        selected_bloc = selected_bloc == (int)_games.size() + (int)_lib.size() + 1 ? (int)_games.size() : selected_bloc;
    }
    if (event == Arcade::KEYRIGHT)
        selected_bloc += selected_bloc < (int)_games.size() ? (int)_games.size() + 1 : 0;
    if (event == Arcade::KEYLEFT)
        selected_bloc -= selected_bloc > (int)_games.size() ? (int)_lib.size() + 1: 0;
    if (selected_bloc < 0)
        selected_bloc = 0;
    if (event == Arcade::ENTER) {
        if (selected_bloc == (int)_games.size())
            return -1;
        else 
            return selected_bloc + 1;
    }
    return 0;
}