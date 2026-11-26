#include <cassert>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace sjtu {
#include "../src.hpp"
}

void check(const std::string &input, const std::vector<std::string> &delimiters) {
    std::vector<char> actual(input.begin(), input.end());
    actual.push_back('\0');
    std::vector<char> expected = actual;
    char *state = nullptr;
    for (unsigned i = 0; i < input.size() + 4; ++i) {
        const char *delim = delimiters[i % delimiters.size()].c_str();
        char *a = sjtu::strtok(i == 0 ? actual.data() : nullptr, delim);
        char *b = ::strtok_r(i == 0 ? expected.data() : nullptr, delim, &state);
        assert((a == nullptr) == (b == nullptr));
        if (a != nullptr) {
            assert(a - actual.data() == b - expected.data());
            assert(std::strcmp(a, b) == 0);
        }
        assert(actual == expected);
    }
}

int main() {
    check("", {"", "abc"});
    check("aaaa", {"a"});
    check("--abc--def--", {"-"});
    check("abcdef", {""});
    check("ab:cd,ef;;gh", {":", ",", ";", ""});
    check("abcdefaedd", {"abd"});
    check("textabcwdefwghi", {"w"});
    char first[] = "a,b";
    char second[] = "c:d";
    assert(std::strcmp(sjtu::strtok(first, ","), "a") == 0);
    assert(std::strcmp(sjtu::strtok(second, ":"), "c") == 0);
    assert(std::strcmp(sjtu::strtok(nullptr, ":"), "d") == 0);

    std::mt19937 random(1351);
    for (int trial = 0; trial < 20000; ++trial) {
        std::string input;
        for (unsigned n = random() % 200; n > 0; --n) {
            input += static_cast<char>(1 + random() % 255);
        }
        std::vector<std::string> delimiters(5);
        for (auto &delim : delimiters) {
            for (unsigned n = random() % 40; n > 0; --n) {
                delim += static_cast<char>(1 + random() % 255);
            }
        }
        check(input, delimiters);
    }
    std::cout << "All strtok tests passed\n";
}
