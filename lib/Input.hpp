#include <vector>
#include <string>

#pragma once

namespace input {

    std::vector<std::string> readLines(const char* fileName);

    std::vector<std::string> split(const std::string& input, const std::string& delimiter);

    std::vector<int> splitInt(const std::string& input, const std::string& delimiter);

    std::vector<long> splitLong(const std::string& input, const std::string& delimiter);

    std::vector<long long> splitLongLong(const std::string& input, const std::string& delimiter);    

    void remove(std::string& input, const char charToRemove);

}
