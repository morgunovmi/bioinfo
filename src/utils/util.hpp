#pragma once

#include <string>
#include <string_view>
#include <vector>

auto read_file_to_string(std::string_view file_path) -> std::string;
auto split_once(const std::string_view string, const std::string_view delim) -> std::pair<std::string_view, std::string_view>;
auto split_once_str(const std::string& string, const std::string_view delim) -> std::pair<std::string, std::string>;
auto tokenize(const std::string_view string, std::string_view delims) -> std::vector<std::string_view>;
auto tokenize_str(const std::string string, std::string_view delims) -> std::vector<std::string>;
