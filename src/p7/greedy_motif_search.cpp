#include <sstream>
#include <fmt/format.h>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <numeric>

#include "p6/profile_most_probable.hpp"
#include "greedy_motif_search.hpp"
#include "utils/util.hpp"

namespace p7 {
[[nodiscard]] auto form_profile_with_laplace(const std::vector<std::string_view>& motifs, std::size_t k) -> p6::profile_mat {
    auto count = std::vector<std::vector<std::size_t>>(4, std::vector<std::size_t>(k, 0));
    for (const auto & str : motifs) {
        for (std::size_t i = 0; i < k; ++i) {
            switch (str[i]) {
                case 'A':
                    ++count[0][i];
                    break;
                case 'C':
                    ++count[1][i];
                    break; case 'G':
                    ++count[2][i];
                    break;
                case 'T':
                    ++count[3][i];
                    break;
            }
        }
    }

    // laplace
    for (auto & row : count) {
        for (auto & val : row) {
            ++val;
        }
    }

    auto profile = p6::profile_mat(4, std::vector<double>(k, 0.0));
    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = 0; j < k; ++j) {
            profile[i][j] = static_cast<double>(count[i][j]) / (motifs.size() + 4); 
        }
    }
    return profile;
} 

[[nodiscard]] auto score_motifs(const std::vector<std::string_view>& motifs, std::size_t k) -> std::size_t {
    std::vector<std::unordered_map<char, std::size_t>> count_maps(k);
    for (const auto & str : motifs) {
        for (std::size_t i = 0; i < k; ++i) {
            ++count_maps[i][str[i]];
        }
    }

    std::vector<char> best_chars{};
    std::ranges::transform(count_maps, std::back_inserter(best_chars), [](auto map){
                               const auto [c, val] = *std::max_element(map.cbegin(), map.cend(),
                                                                       [](auto p1, auto p2){ return p1.second < p2.second; }); 
                               return c;
                           });

    std::vector<std::size_t> misses(k, 0);
    for (const auto & row : motifs) {
        for (std::size_t i = 0; i < k; ++i) {
            if (row[i] != best_chars[i]) {
                ++misses[i];
            }
        }
    }

    return std::accumulate(misses.cbegin(), misses.cend(), 0);
}

[[nodiscard]] auto greedy_motif_search(std::size_t k, std::size_t t, const std::vector<std::string_view>& dna) -> std::vector<std::string_view> {
    std::vector<std::string_view> best_motifs{};
    for (const auto & str : dna) {
        best_motifs.emplace_back(str.substr(0, k));
    }

    for (std::size_t i = 0; i < dna[0].size() - k + 1; ++i) {
        std::vector<std::string_view> motifs{};
        motifs.emplace_back(dna[0].substr(i, k));
        for (std::size_t j = 1; j < t; ++j) {
            const auto profile = form_profile_with_laplace(motifs, k);
            motifs.emplace_back(p6::find_profile_most_probable_kmer(dna[j], k, profile));
        }

        if (score_motifs(motifs, k) < score_motifs(best_motifs, k)) {
            best_motifs = std::move(motifs);
        }
    }

    return best_motifs;
}

void solve() {
    const auto file_str = read_file_to_string("samples/GreedyMotifSearchPseudocounts/rosalind_ba2e.txt");
    const auto [num_str, dna_str] = split_once(file_str, "\n");

    std::stringstream ss{num_str.data()};
    std::size_t k = 0, t = 0;
    ss >> k >> t;

    const auto dna = tokenize(dna_str, "\n\r\t");
    for (const auto & str : greedy_motif_search(k, t, dna)) {
        fmt::print("{}\n", str);
    }
}
}
