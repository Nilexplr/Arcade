/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Core
*/

#include "Core.hpp"

Arcade::Core::Core(const std::string &path) :
_loader(), _objMenu(), _lib(), _actualGame(0), _actualGraph(0),_game(),_graph(),
_menu(true), _application(true), _counterMenu(true)
{
    _lib.push_back(_loader.loadLib(path));
    _graph.push_back(_loader.getInstance<IGraph>(_lib[0], "Lib"));
    _nameactual = _graph[0]->getName();
    loadGraphical();
    loadGame();
    _graph[_actualGraph]->openWindow();
    _objMenu.loadGameName(getGameName());
    _objMenu.loadLibName(getLibName());
}

Arcade::Core::~Core()
{
}

void Arcade::Core::mainLoop()
{
    while (_application) {
        if (_menu)
            menuLoop();
        else
            gameLoop();
    }
    _graph[_actualGraph]->closeWindow();
}

void Arcade::Core::menuLoop()
{
    int update;

    while (_menu) {
        _graph[_actualGraph]->updateWindow();
        _graph[_actualGraph]->drawObject("title", _graph[_actualGraph]->getPosMenu("posTitle"));
        _graph[_actualGraph]->drawText(_graph[_actualGraph]->getPosMenu("posUndertitle"), 30, "AN ARCADE GAME APPLICATION");
        if (!_objMenu.getValid())
            _objMenu.askName(_graph[_actualGraph]);
        else {
            _objMenu.handlingMenu(_graph[_actualGraph]);
        }
        _event = _graph[_actualGraph]->getEvent();
        analyseEvent();
        update = _objMenu.update(_event);
        if (update == -1) {
            _menu = false;
            _application = false;
        }
        if (update > 0 && update <= (int)_graph.size()) {
            _menu = false;
            _actualGame = update - 1;
            _graph[_actualGraph]->loadAsset(_game[_actualGame]->getName());
        }
        if (update > (int)_graph.size())
            changeGraphical((update - ((int)_game.size() + 2)));
    }
    _counterMenu = false;
}

void Arcade::Core::gameLoop()
{
    _graph[_actualGraph]->loadAsset(_game[_actualGame]->getName());
	while (!_menu) {
		_graph[_actualGraph]->updateWindow();
		_event = _graph[_actualGraph]->getEvent();
        analyseEvent();
        if (_game[_actualGame]->gameOver() == true) {
            _graph[_actualGraph]->drawBox({45, 35}, {20,27});
            _graph[_actualGraph]->drawText({50, 47}, 20, "GameOver");
            _graph[_actualGraph]->drawText({53, 40}, 20, "Press enter to restart the game");
            if (_event == ENTER)
                _game[_actualGame]->resetGame();
            continue;
        }
		_game[_actualGame]->updateGame(_event);
		_graph[_actualGraph]->drawMap(_game[_actualGame]->getMap(), _graph[_actualGraph]->getPosMenu("posMap"));
		_graph[_actualGraph]->drawCharacter(_game[_actualGame]->getCharacter(), _graph[_actualGraph]->getPosMenu("posMap"));
        _objMenu.drawHUD(_graph[_actualGraph], _game[_actualGame]->getName(), _game[_actualGame]->getScore());
	}
}

void Arcade::Core::changeGame(int id)
{
    _actualGame = id;

    if (_actualGame == (size_t)(0 - 1))
        _actualGame = _game.size() - 1;
    if (_actualGame >= _game.size())
        _actualGame = 0;
    _graph[_actualGraph]->loadAsset(_game[_actualGame]->getName());
}

void Arcade::Core::changeGraphical(int id)
{
    _graph[_actualGraph]->closeWindow();
    _actualGraph = id;

    if (_actualGraph == (size_t)(0 - 1))
        _actualGraph = _graph.size() - 1;
    if (_actualGraph >= _graph.size())
        _actualGraph = 0;
    _graph[_actualGraph]->loadAsset(_game[_actualGame]->getName());
    _graph[_actualGraph]->openWindow();
}

void Arcade::Core::loadGame()
{
    std::vector<std::string> pathname;
    DIR *dir;
    int i = _graph.size();
    struct dirent *ent;

    if ((dir = opendir("./games")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string result = ent->d_name;
            if (result.find(".so") != std::string::npos)
                pathname.push_back(result);
        }
        closedir(dir);
    } else
        throw std::exception();
    for (auto x : pathname) {
        _lib.push_back(_loader.loadLib("./games/" + x));
        _game.push_back(_loader.getInstance<IGame>(_lib[i], "Game"));
        i++;
    }

}

void Arcade::Core::loadGraphical()
{
    std::vector<std::string> pathname;
    DIR *dir;
    struct dirent *ent;
    int i = 1;

    if ((dir = opendir("./lib")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string result = ent->d_name;
            if (result.find(".so") != std::string::npos  && result.find(_nameactual) == std::string::npos)
                pathname.push_back(result);
        }
        closedir(dir);
    } else
        throw std::exception();
    for (auto x : pathname) {
        _lib.push_back(_loader.loadLib("./lib/" + x));
        _graph.push_back(_loader.getInstance<IGraph>(_lib[i], "Lib"));
        i++;
    }
}

void Arcade::Core::analyseEvent()
{
    if (_event == CLOSE) {
        _application = false;
        _menu = false;
    }
    if (_event == ECHAP) {
        if (!_counterMenu)
            _menu = _menu == true ? false : true;
    }
    if (_event == NEXTGAME)
        changeGame(_actualGame + 1);
    if (_event == PREVGAME)
        changeGame(_actualGame - 1);
    if (_event == NEXTLIB)
        changeGraphical(_actualGraph + 1);
    if (_event == PREVLIB)
        changeGraphical(_actualGraph -1);
}

std::vector<std::string> Arcade::Core::getGameName() const
{
    std::vector<std::string> result;

    for (auto x : _game)
        result.push_back(x->getName());
    return result;
}

std::vector<std::string> Arcade::Core::getLibName() const
{
    std::vector<std::string> result;

    for (auto x : _graph)
        result.push_back(x->getName());
    return result;
}
