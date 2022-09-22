#include <fmt/format.h>
#include <sstream>
#include <random>

#include "randomized_motif_search.hpp"
#include "p7/greedy_motif_search.hpp"
#include "utils/util.hpp"

namespace p8 {
auto generate_motifs(const p6::profile_mat& profile, const std::vector<std::string_view>& dna, std::size_t k) {
    std::vector<std::string_view> motifs{};
    for (const auto & str : dna) {
        motifs.push_back(p6::find_profile_most_probable_kmer(str, k, profile));
    }
    return motifs;
}

auto randomized_motif_search(std::size_t k, std::size_t t, const std::vector<std::string_view>& dna) -> std::vector<std::string_view> {
    std::random_device rd{};
    std::default_random_engine dre{rd()};
    std::uniform_int_distribution distr{0, static_cast<int>(dna[0].size() - k)};

    std::vector<std::string_view> motifs{};
    for (const auto & str : dna) {
        motifs.emplace_back(str.substr(distr(dre), k));
    }

    auto best_motifs = motifs;

    while (true) {
        const auto profile = p7::form_profile_with_laplace(motifs, k);
        
        motifs = generate_motifs(profile, dna, k);
        if (p7::score_motifs(motifs, k) < p7::score_motifs(best_motifs, k)) {
            best_motifs = motifs;
        } else {
            return best_motifs;
        }
    }
    return best_motifs;
}

void solve() {
    const auto file_str = read_file_to_string("samples/RandomizedMotifSearch/rosalind_ba2f.txt");
    const auto [num_str, dna_str] = split_once(file_str, "\n");

    std::stringstream ss{num_str.data()};
    std::size_t k = 0, t = 0;
    ss >> k >> t;

    const auto dna = tokenize(dna_str, "\n\r\t");

    std::size_t best_score = LLONG_MAX;
    std::vector<std::string_view> best_motifs;
    for (std::size_t i = 0; i < 1000; ++i) {
        const auto motifs = randomized_motif_search(k, t, dna);
        const auto score = p7::score_motifs(motifs, k);
        if (score < best_score) {
            best_score = score;
            best_motifs = std::move(motifs);
        }
    }

    for (const auto & str : best_motifs) {
        fmt::print("{}\n", str);
    }
}
}
