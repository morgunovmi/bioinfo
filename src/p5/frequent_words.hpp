#pragma once

#include <vector>
#include <string_view>

namespace p5 {
auto neighbors(std::string_view text, std::size_t d) -> std::vector<std::string>;
auto find_freq_words_with_mismatches(std::string_view text, std::size_t k, std::size_t d) -> std::vector<std::string>;
void solve();
}
