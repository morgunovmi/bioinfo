#include <fmt/format.h>
#include <cstdint>

#include "utils/util.hpp"
#include "approx_occurences.hpp"

namespace p4 {
auto hamming_distance(std::string_view s1, std::string_view s2) -> std::size_t {
    std::size_t count = 0;
    for (std::size_t i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            ++count;
        }
    }
    return count;
}

auto find_approx_occurences(std::string_view pattern, std::string_view text, std::size_t d) -> std::vector<std::size_t> {
    std::vector<std::size_t> indices{};
    for (std::size_t i = 0; i < text.size() - pattern.size() + 1; ++i) {
        if (hamming_distance(text.substr(i, pattern.size()), pattern) <= d) {
            indices.push_back(i);
        }
    }
    return indices;
}

void solve() {
    const auto genome = read_file_to_string("samples/ApproxOccurences/dataset_240221_6.txt");
    const auto [pattern, s] = split_once(genome, "\n");
    const auto [text, d_str] = split_once(s, "\n");
    const auto d = std::stoi(d_str.data());

    const auto o = find_approx_occurences(pattern, text, d);
    for (const auto & idx : o) {
        fmt::print("{} ", idx);
    }
    fmt::print("\n{}\n", o.size());
}
}
