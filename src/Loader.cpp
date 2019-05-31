/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Loader
*/

#include "Loader.hpp"

Loader::Loader()
{
}

Loader::~Loader()
{
}

void *Loader::loadLib(const std::string &path)
{
    void *lib = dlopen(path.c_str(), RTLD_NOW | RTLD_LAZY);

    if (!lib) {
        std::cerr << dlerror() << std::endl;
        throw std::exception();
    }
    return lib;
}

void Loader::closeLib(void *lib)
{
    if (dlclose(lib) != 0)
		std::cerr << dlerror() << std::endl;
}
