#include <fmt/format.h>
#include <ranges>
#include <algorithm>
#include <unordered_map>
#include <cassert>

#include "peptide_encoding.hpp"
#include "utils/util.hpp"

const std::unordered_map<std::string, char> geneticCode {
    {"AAA", 'K'},
    {"AAC", 'N'},
    {"AAG", 'K'},
    {"AAU", 'N'},
    {"ACA", 'T'},
    {"ACC", 'T'},
    {"ACG", 'T'},
    {"ACU", 'T'},
    {"AGA", 'R'},
    {"AGC", 'S'},
    {"AGG", 'R'},
    {"AGU", 'S'},
    {"AUA", 'I'},
    {"AUC", 'I'},
    {"AUG", 'M'},
    {"AUU", 'I'},
    {"CAA", 'Q'},
    {"CAC", 'H'},
    {"CAG", 'Q'},
    {"CAU", 'H'},
    {"CCA", 'P'},
    {"CCC", 'P'},
    {"CCG", 'P'},
    {"CCU", 'P'},
    {"CGA", 'R'},
    {"CGC", 'R'},
    {"CGG", 'R'},
    {"CGU", 'R'},
    {"CUA", 'L'},
    {"CUC", 'L'},
    {"CUG", 'L'},
    {"CUU", 'L'},
    {"GAA", 'E'},
    {"GAC", 'D'},
    {"GAG", 'E'},
    {"GAU", 'D'},
    {"GCA", 'A'},
    {"GCC", 'A'},
    {"GCG", 'A'},
    {"GCU", 'A'},
    {"GGA", 'G'},
    {"GGC", 'G'},
    {"GGG", 'G'},
    {"GGU", 'G'},
    {"GUA", 'V'},
    {"GUC", 'V'},
    {"GUG", 'V'},
    {"GUU", 'V'},
    {"UAA", '*'},
    {"UAC", 'Y'},
    {"UAG", '*'},
    {"UAU", 'Y'},
    {"UCA", 'S'},
    {"UCC", 'S'},
    {"UCG", 'S'},
    {"UCU", 'S'},
    {"UGA", '*'},
    {"UGC", 'C'},
    {"UGG", 'W'},
    {"UGU", 'C'},
    {"UUA", 'L'},
    {"UUC", 'F'},
    {"UUG", 'L'},
    {"UUU", 'F'}
};

namespace p16 {
    auto transcribe(std::string_view genome) -> std::string {
        std::vector<char> res{};
        std::transform(genome.begin(), genome.end(), std::back_inserter(res), [](char c){ return c == 'T' ? 'U' : c; });
        return {res.begin(), res.end()};
    }

    auto get_encoded_peptide(const std::string& genome) -> std::string {
        assert(genome.size() % 3 == 0);
        std::string peptide{""};
        for (std::size_t i = 0; i < genome.size() / 3; ++i) {
            peptide += geneticCode.at(genome.substr(3 * i, 3));
        }

        return peptide;
    }

    auto get_reverse_complement(std::string_view genome) -> std::string {
        namespace rng = std::ranges;
        auto rev = std::string{genome.rbegin(), genome.rend()};
        rng::transform(rev, rev.begin(), [](auto c)
                       {
                                              switch (c) {
                                                  case 'A':
                                                      return 'T';
                                                  case 'T':
                                                      return 'A';
                                                  case 'G':
                                                      return 'C';
                                                  case 'C':
                                                      return 'G';
                                                  default:
                                                      return 'A';
                                              } });
        return rev;
    }

    auto find_substrings_encoding_peptide(std::string_view text, std::string_view peptide) -> std::vector<std::string_view>
    {
        std::vector<std::string_view> res{};
        uint32_t k = peptide.size() * 3;
        for (std::size_t i = 0; i < text.size() - k + 1; ++i) {
            if (get_encoded_peptide(transcribe(text.substr(i, k))) == peptide ||
                get_encoded_peptide(transcribe(get_reverse_complement(text.substr(i, k)))) == peptide) {
                    res.emplace_back(text.substr(i, k));
                }
        }
        return res;
    }

    void solve() {
        const auto file_str = read_file_to_string("samples/PeptideEncoding/rosalind_ba4b.txt");
        const auto [text, peptide] = split_once(file_str, "\n");
        for (const auto &str : find_substrings_encoding_peptide(text, peptide)) {
            fmt::print("{}\n", str);
        }
    }
}