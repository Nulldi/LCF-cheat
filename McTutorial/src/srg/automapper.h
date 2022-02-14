#pragma once
#include <string>

class c_automapper
{
public:
	bool init();
	std::string map(std::string unObfCLassName);

private:
	std::string classMappings;
};

extern c_automapper* automapper;