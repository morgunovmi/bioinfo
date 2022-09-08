#pragma once

#include <string>
#include <string_view>

auto read_file_to_string(std::string_view file_path) -> std::string;
auto split_once(const std::string_view string, const std::string_view delim) -> std::pair<std::string_view, std::string_view>;
