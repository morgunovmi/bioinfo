#include <fmt/format.h>

#include "distance_between_pattern_and_strings.hpp"
#include "p4/approx_occurences.hpp"
#include "utils/util.hpp"

namespace p10 {
auto distance_between_pattern_and_strings(std::string_view pattern, const std::vector<std::string_view>& dna) -> std::size_t {
    const auto k = pattern.size();
    std::size_t distance = 0;
    for (const auto & text : dna) {
        std::size_t ham_dist = LLONG_MAX;
        for (std::size_t i = 0; i < text.size() - k + 1; ++i) {
            const auto curr_ham_dist = p4::hamming_distance(text.substr(i, k), pattern);
            if (ham_dist > curr_ham_dist) {
                ham_dist = curr_ham_dist;
            }
        } 
        distance += ham_dist;
    }
    return distance;
}

void solve() {
    const auto file_str = read_file_to_string("samples/DistanceBetweenPatternAndStrings/rosalind_ba2h.txt");
    const auto [pattern, dna_str] = split_once(file_str, "\n");
    const auto dna = tokenize(dna_str, " ");

    fmt::print("{}\n", distance_between_pattern_and_strings(pattern, dna));
}
}
