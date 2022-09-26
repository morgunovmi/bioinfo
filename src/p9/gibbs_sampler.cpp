#include <fmt/format.h>
#include <numeric>
#include <ranges>
#include <algorithm>
#include <random>
#include <cassert>
#include <sstream>

#include "gibbs_sampler.hpp"
#include "p7/greedy_motif_search.hpp"
#include "utils/util.hpp"

namespace p9 {
std::random_device rd{};
std::default_random_engine dre{rd()};
std::uniform_real_distribution distr{0.0, 1.0};

auto random(std::vector<double>& raw_distr) -> std::size_t {
    std::ranges::transform(raw_distr, raw_distr.begin(), 
                           [&raw_distr](auto val){ return val / std::accumulate(raw_distr.begin(), raw_distr.end(), 0.0); });

    const auto val = distr(dre);
    double start = 0.0;
    for (std::size_t i = 0; i < raw_distr.size(); ++i) {
        if (val > start && val <= start + raw_distr[i]) {
            return i;
        }
        start += raw_distr[i];
    }
}

auto get_pattern_prob(std::string_view pattern, std::size_t k, const p6::profile_mat profile) -> double {
    fmt::print("Pattern in get_pattern_prob : {}\n", pattern);
    double cur_prob = 0.0;
    for (std::size_t j = 0; j < k; ++j) {
        std::size_t row_index = 0;
        switch (pattern[j]) {
            case 'A':
                row_index = 0;
                break;
            case 'C':
                row_index = 1;
                break;
            case 'G':
                row_index = 2;
                break;
            case 'T':
                row_index = 3;
                break;
        }

        const auto char_prob = profile[row_index][j];
        if (j == 0) {
            cur_prob = char_prob;
        } else {
            cur_prob *= char_prob;
        }
    }
    return cur_prob;
}

auto profile_randomly_generated_kmer(std::string_view text, std::size_t k, const p6::profile_mat& profile) -> std::string_view {
    fmt::print("Dna string in profile_randomly_generated_kmer: {}\n", text);
    std::vector<double> probs{};
    for (std::size_t i = 0; i < text.size() - k; ++i) {
        probs.emplace_back(get_pattern_prob(text.substr(i, k), k, profile));
    }

    /*
    for (const auto & prob : probs) {
        fmt::print("{} ", prob);
    }
    fmt::print("\n");
    */

    return text.substr(random(probs), k);
}

auto gibbs_sampler(const std::vector<std::string_view>& dna, std::size_t k, std::size_t t, std::size_t n) -> std::vector<std::string_view> {
    fmt::print("Dna one gibbs_sampler entry :\n");
    for (const auto & str : dna) {
        fmt::print("{}\n", str);
    }
    fmt::print("\n");

    std::uniform_int_distribution index_distr{0, static_cast<int>(dna[0].size() - k)};

    std::vector<std::string_view> motifs{};
    for (const auto & str : dna) {
        motifs.emplace_back(str.substr(index_distr(dre), k));
    }

    fmt::print("Randomly selected motifs :\n");
    for (const auto & str : motifs) {
        fmt::print("{}\n", str);
    }
    fmt::print("\n");

    auto best_motifs = motifs;

    std::uniform_int_distribution motif_distr{0, static_cast<int>(motifs.size() - 1)};
    for (std::size_t j = 0; j < n; ++j) {
        const std::size_t i = motif_distr(dre);
        std::vector<std::string_view> reduced_motifs{};
        for (std::size_t k = 0; k < motifs.size(); ++k) {
            if (k != i) {
                reduced_motifs.push_back(motifs[k]);
            }
        }

        fmt::print("Reduced motifs :\n");
        for (const auto & str : reduced_motifs) {
            fmt::print("{}\n", str);
        }
        fmt::print("Reduced motifs count : {}\n\n", reduced_motifs.size());
        assert(reduced_motifs.size() == 4);

        const auto profile = p7::form_profile_with_laplace(reduced_motifs, k);

        fmt::print("Profile : \n");
        for (const auto & row : profile) {
            for (const auto & val : row) {
                fmt::print("{} ", val);
            }
            fmt::print("\n");
        }
        fmt::print("\n");

        motifs[i] = profile_randomly_generated_kmer(dna[i], k, profile);
        if (p7::score_motifs(motifs, k) < p7::score_motifs(best_motifs, k)) {
            best_motifs = motifs;
        }
    }
    return best_motifs;
}

void solve() {
    const auto file_str = read_file_to_string("samples/GibbsSampler/sample.txt");
    const auto [num_str, dna_str] = split_once(file_str, "\n");

    std::stringstream ss{num_str.data()};
    std::size_t k = 0, t = 0, n = 0;
    ss >> k >> t >> n;

    const auto dna = tokenize(dna_str, " ");
    for (const auto & str : gibbs_sampler(dna, k, t, n)) {
        fmt::print("{} ", str);
    }
}
} 
