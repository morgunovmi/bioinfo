#include <exception>
#include <fstream>
#include "util.hpp"

auto read_file_to_string(std::string_view file_path) -> std::string {
    if (auto ifs = std::ifstream{ file_path.data() }) {
        return { std::istreambuf_iterator<char>{ifs}, {} };
    }
    throw std::runtime_error{"Failed to read file to string"};
}

auto split_once(std::string_view string, const std::string_view delim) -> std::pair<std::string_view, std::string_view> {
    auto pos = string.find(delim);
    if (pos != std::string::npos) {
        return { string.substr(0, pos), string.substr(pos + 1) };
    }
    throw std::runtime_error{"Couldn't split string"};
}

auto tokenize(std::string_view string) -> std::vector<std::string_view> {
    const std::string delims{"\r\n\t"};
    std::vector<std::string_view> parts{};
    for (auto beg = string.find_first_not_of(delims); beg != std::string::npos;) {
        auto end = string.find_first_of(delims, beg);
        parts.emplace_back(string.substr(beg, end - beg));
        beg = string.find_first_not_of(delims, end);
    }
    return parts;
}
