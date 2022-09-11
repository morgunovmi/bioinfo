#include <map>
#include <algorithm>
#include <sstream>
#include <fmt/format.h>

#include "frequent_words.hpp"
#include "p4/approx_occurences.hpp"
#include "utils/util.hpp"

namespace p5 {
auto neighbors(std::string_view pattern, std::size_t d) -> std::vector<std::string> {
    const auto p = std::string{pattern};
    if (d == 0) {
        return {p};
    }
    if (pattern.size() == 1) {
        return {"A", "T", "G", "C"};
    }
    std::vector<std::string> neighborhood{};
    const auto suffix = p.substr(1);
    const auto suffix_neighbors = neighbors(suffix, d);
    for (const auto & text : suffix_neighbors) {
        if (p4::hamming_distance(suffix, text) < d) {
            for (const auto & nucl : {"A", "T", "G", "C"}) {
                neighborhood.push_back(nucl + text);
            }
        } else {
            neighborhood.push_back(p[0] + text);
        }
    }
    return neighborhood;
}

auto find_freq_words_with_mismatches(std::string_view text, std::size_t k, std::size_t d) -> std::vector<std::string_view> {
    std::vector<std::string_view> patterns{};
    std::map<std::string_view, std::size_t> freq_map{};
    for (std::size_t i = 0; i < text.size() - k; ++i) {
        const auto neighborhood = neighbors(text.substr(i, k), d);
        fmt::print("Neighborhood: \n");
        for (const auto & n : neighborhood) {
            fmt::print("{}\n", n);
        }
        fmt::print("Neighborhood ended\n");
        for (const auto & neighbor : neighborhood) {
            ++freq_map[neighbor];
        }
    }
    for (const auto & pair : freq_map) {
        fmt::print("{} : {}\n", pair.first, pair.second);
    }
    const auto [m_pattern, m] = *std::max_element(freq_map.cbegin(), freq_map.cend(),
                                                  [](auto p1, auto p2){ return p1.second < p2.second; }); 
    fmt::print("Max pattern : {} : {}", m_pattern, m);
    for (const auto & pair : freq_map) {
        if (freq_map[pair.first] == m) {
            patterns.push_back(pair.first);
        }
    }
    return patterns;
}

void solve() {
    const auto str = read_file_to_string("samples/FrequentWords/sample.txt");
    const auto [genome, numString] = split_once(str, "\n");

    std::size_t k = 0, d = 0;
    std::stringstream numStream{numString.data()};
    numStream >> k >> d;

    fmt::print("k : {}, d : {}\n", k, d);

    for (const auto & pattern : find_freq_words_with_mismatches(genome, k, d)) {
        fmt::print("{} ", pattern);
    }
}
}
