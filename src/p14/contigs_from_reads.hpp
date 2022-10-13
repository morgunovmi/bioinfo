#pragma once

#include <vector>
#include <string>

namespace p14 {
auto generate_contigs(const std::vector<std::string>& reads) -> std::vector<std::string>;
void solve();
}
