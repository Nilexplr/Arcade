/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** main
*/

#include "Core.hpp"

static void print_usage()
{
	std::cout << "USAGE:\t./arcade [Graphical_lib_path]" << std::endl 
	<< "\nEXEMPLE:\t./arcade ./lib/lib_arcade_sfml.so"  << std::endl << std::endl;
	std::cout << "CONTROLLER:" << std::endl << "\tA :\tprevious game library" << std::endl;
	std::cout << "\tZ :\tnext game library" << std::endl;
	std::cout << "\tQ :\tprevious graphics library" << std::endl;
	std::cout << "\tS :\tnext graphics library" << std::endl;
	std::cout << "\tW :\tButton 1" << std::endl;
	std::cout << "\tX :\tButton 2" << std::endl;
	std::cout << "\tENTER :\tSelect" << std::endl;
	std::cout << "\tECHAP :\tMenu" << std::endl;
	exit(84);
}

int main(int ac, char **av)
{
	if (ac != 2 || std::string(av[1]) == "-h")
		print_usage();
	try {
		Arcade::Core core(av[1]);
		core.mainLoop();
	} catch(std::exception &e) {
		e.what();
		return(84);
	}
	return 0;
}
