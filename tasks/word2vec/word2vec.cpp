#include "word2vec.h"

#include <vector>

int64_t Multiply(std::vector<int> a, std::vector<int> b) {
    int64_t ans = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        ans += static_cast<int64_t>(a[i]) * static_cast<int64_t>(b[i]);
    }
    return ans;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int64_t maximal = Multiply(vectors[0], vectors[1]);
    for (size_t i = 1; i < words.size(); ++i) {
        maximal = std::max(maximal, Multiply(vectors[0], vectors[i]));
    }
    std::vector<std::string> ans;
    for (size_t i = 1; i < words.size(); ++i) {
        if (Multiply(vectors[0], vectors[i]) == maximal) {
            ans.push_back(words[i]);
        }
    }
    return ans;
}