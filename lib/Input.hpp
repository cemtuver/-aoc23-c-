#include <vector>
#include <string>

#ifndef INPUT_HPP
#define INPUT_HPP

namespace input {

    std::vector<std::string> readLines(const char* fileName);

    std::vector<std::string> split(const std::string& input, const std::string& delimiter);

    std::vector<int> splitInt(const std::string& input, const std::string& delimiter);

}

#endif