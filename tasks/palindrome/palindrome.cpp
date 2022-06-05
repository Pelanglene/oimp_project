#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t i = 0, j = str.size() - 1;
    while (i < j) {
        if (str[i] == ' ') {
            ++i;
            continue;
        }
        if (str[j] == ' ') {
            --j;
            continue;
        }

        if (str[i] != str[j]) {
            return false;
        }
        ++i;
        --j;
    }
    return true;
}