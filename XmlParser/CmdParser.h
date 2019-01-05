#ifndef CMD_PARSER_H
#define CMD_PARSER_H
#include <string>


class CmdParser
{
public:
	bool Pars();
private:
	std::string line;
	std::string cmd;
};



#endif