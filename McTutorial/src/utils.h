#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

class c_utils
{
public:
	std::vector<std::string> splitString(std::string text, char delimiter);
};

extern c_utils* utils;