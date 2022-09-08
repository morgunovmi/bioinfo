#include <fmt/format.h>

#include "utils/util.hpp"
#include "pattern_count.hpp"

namespace p1 {
auto pattern_count(std::string_view text, std::string_view pattern) -> std::vector<std::size_t> {
    std::vector<std::size_t> result{};

    for (std::size_t i = 0; i < text.size() - pattern.size() + 1; ++i) {
        if (text.substr(i, pattern.size()) == pattern) {
            result.push_back(i);
        }
    }
    return result;
}

void solve() {
    const auto debug_txt = read_file_to_string("samples/PatternMatching/rosalind_ba1d.txt");
    const auto [pattern, text] = split_once(debug_txt, "\n");
    for (const auto & index : pattern_count(text, pattern)) {
        fmt::print("{} ", index);
    }
}
}
