#include <cstdio>
#include <cstring>
#include <iostream>

std::string get_mime_type(const std::string& filename) {
    std::string command = "file --brief --mime-type " + filename;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "";
    }
    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL) {
            result += buffer;
        }
    }
    pclose(pipe);
    result.erase(result.find_last_not_of("\n\r") + 1);
    return result;
}

