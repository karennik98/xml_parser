#include "pch.h"
#include "Xml.h"
#include <iostream>
#include <string>

int main()
{
	Read xmlFile("Xml.txt");
	xmlFile.Parse();
	xmlFile.getAllTags();
	//std::string cmd;
	/*std::cout << "Commands:\n";
	std::cout << "Take tag value:(val):\n";
	std::cout << "...  ";
	std::cin >> cmd;
	if (cmd == "val")
	{
		std::string name;
		std::cout << "Enter Tag Name: \n";
		std::cin >> name;
		std::cout << xmlFile.getTagValue(name) << std::endl;
	}*/
	return 0;
}
