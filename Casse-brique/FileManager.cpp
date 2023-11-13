#include "FileManager.h"
#include <iostream>
#include <fstream>

std::string FileManager::returnText(const char* path) {
	std::string text;
	
	std::ifstream file(path);

	file.seekg(0, std::ios::end); 

	int taille;
	taille = file.tellg();

	file.seekg(0, std::ios::beg);
	char a;

	for (int i = 0; i < taille; i++)
	{
		file.get(a);
		text += a;
	}

	return text;
}
