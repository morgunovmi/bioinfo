#include "peptide_total_mass.hpp"

#include "utils/util.hpp"
#include <fstream>

#include <iostream>
#include <fmt/format.h>
#include <set>

std::vector<u64> massTable{57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};

namespace p17 {
    auto count_peptides_with_mass(u64 mass) -> u64 {
        const auto m = massTable.size();
        std::vector<u64> table(mass + 1, 0);
        table[0] = 1;

        for (std::size_t n = 1; n <= mass; ++n) {
            u64 accum = 0;
            for (std::size_t i = 0; i < m; ++i) {
                if (massTable[i] <= n) {
                    accum += table[n - massTable[i]];
                }
            }
            table[n] = accum;
        }
        return table[mass];
    }

    void solve() {
        u64 mass = 0;
        std::cin >> mass;
        fmt::print("{}\n", count_peptides_with_mass(mass));
    }
}