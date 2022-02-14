#include "utils.h"

c_utils* utils = new c_utils;

std::vector<std::string> c_utils::splitString(std::string input, char delimiter) {
    std::vector<std::string> elements;
    std::string temp = "";
    for (int i = 0; i < input.length(); ++i) {

        if (input[i] == delimiter) {
            elements.push_back(temp);
            temp = "";
        }
        else {
            temp.push_back(input[i]);
        }

    }
    elements.push_back(temp);

    return elements;
}