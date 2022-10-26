#pragma once

#include <cstdint>

using u64 = uint64_t;
namespace p17 {
    auto count_peptides_with_mass(u64 mass) -> u64;
    void solve();
}