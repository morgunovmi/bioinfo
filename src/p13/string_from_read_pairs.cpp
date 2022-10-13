#include <sstream>
#include <fmt/format.h>

#include "utils/util.hpp"
#include "string_from_read_pairs.hpp"

namespace p13 {
auto string_from_read_pairs(const std::vector<std::string_view>& read_pairs, uint32_t k, uint32_t d) -> std::string {

}

void solve() {
    const auto file_str = read_file_to_string("samples/StringFromReadPairs/sample1.txt");
    const auto [num_str, read_str] = split_once(file_str, "\n");
    const auto read_pairs = tokenize(read_str, "\n");

    uint32_t k = 0, d = 0;
    std::stringstream ss{num_str.data()};
    ss >> k >> d;

    fmt::print("{}\n", string_from_read_pairs(read_pairs, k, d));
}
}
