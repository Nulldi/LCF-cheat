#include "automapper.h"
#include "../utils.h"
#include "../../zip/zip.h"
#include <Windows.h>

c_automapper* automapper = new c_automapper;

bool c_automapper::init() {
    void* buf = NULL;
    size_t bufsize;

    char username[257];
    DWORD username_len = 257;
    GetUserName(username, &username_len);

    struct zip_t* zip = zip_open(std::string("C:\\Users\\" + std::string(username) + "\\.lunarclient\\offline\\1.8\\lunar-prod-optifine.jar").c_str(), 0, 'r');
    {
        zip_entry_open(zip, "patch/v1_8/mappings.txt");
        {
            zip_entry_read(zip, &buf, &bufsize);
        }
        zip_entry_close(zip);
    }
    zip_close(zip);

    this->classMappings = std::string((char*)buf);

    free(buf);
	return true;
}

std::string c_automapper::map(std::string unObfCLassName) {
    std::istringstream lines(this->classMappings);
    std::string current_line;

    while (std::getline(lines, current_line)) {
        std::vector<std::string> split = utils->splitString(current_line, ' ');
        if (split[1] == unObfCLassName) {
            std::vector<std::string> className = utils->splitString(split[0], '.');
            return className[3];
        }
    }
}