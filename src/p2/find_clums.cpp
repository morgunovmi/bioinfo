#include <sstream>
#include <fmt/format.h>
#include <algorithm>

#include "find_clumps.hpp"
#include "utils/util.hpp"

namespace p2 {
auto frequency_table(std::string_view text, std::size_t k) -> std::map<std::string_view, std::size_t> {
    std::map<std::string_view, std::size_t> freq_table{};
    for (std::size_t i = 0; i < text.size() - k; ++i) {
        const auto pattern = text.substr(i, k);
        freq_table[pattern]++;
    }
    return freq_table;
}

auto find_clumps(std::string_view genome, std::size_t k, std::size_t L, std::size_t t) -> std::vector<std::string_view> {
    std::vector<std::string_view> patterns{};
    for (std::size_t i = 0; i < genome.size() - L; ++i) {
        const auto freq_table = frequency_table(genome.substr(i, L), k);
        for (const auto & pair : freq_table) {
            if (pair.second >= t) {
                patterns.emplace_back(pair.first);
            }
        }
    }
    return patterns;
}

void solve() {
    const auto debug_txt = read_file_to_string("samples/ClumpFinding/rosalind_ba1e.txt");
    const auto [genome, numString] = split_once(debug_txt, "\n");

    std::size_t k = 0, L = 0, t = 0;
    std::stringstream numStream{numString.data()};
    numStream >> k >> L >> t;

    auto clumps = find_clumps(genome, k, L, t);
    clumps.erase(std::unique(clumps.begin(), clumps.end()),clumps.end());

    for (const auto & clump : clumps) {
        fmt::print("{} ", clump);
    }
}
}
