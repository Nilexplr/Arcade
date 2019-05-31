/*
** EPITECH PROJECT, 2019
** OOP_arcade_2018
** File description:
** Loader
*/

#ifndef LOADER_HPP_
#define LOADER_HPP_
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <exception>
#include <memory>

class Loader {
	public:
		Loader();
		~Loader();
		void *loadLib(const std::string &path);
		void closeLib(void *lib);
		template<typename T>
		std::shared_ptr<T> getInstance(void *lib, const std::string &type) {
			using allocClass = T *(*)();
			using deleteClass = void (*)(T *);

			auto allocFunc = reinterpret_cast<allocClass>(
					dlsym(lib, const_cast<char*>(std::string("allocator" + type).c_str())));
			auto deleteFunc = reinterpret_cast<deleteClass>(
					dlsym(lib, const_cast<char*>(std::string("deleter" + type).c_str())));
			if (!allocFunc || !deleteFunc) {
				throw std::exception();
			}
			return std::shared_ptr<T>(
					allocFunc(),
					[deleteFunc](T *p){ deleteFunc(p); });
		}
	protected:
	private:
};

#endif /* !LOADER_HPP_ */
