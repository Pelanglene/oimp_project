#include "unixpath.h"
#include <vector>

using Path = std::vector<std::string>;

Path Split(std::string_view dir) {
    std::vector<std::string> ans;
    std::string cur;
    for (auto u : dir) {
        if (u == '/') {
            if (!cur.empty()) {
                ans.push_back(cur);
            }
            cur = "";
        } else {
            cur += u;
        }
    }
    if (!cur.empty()) {
        ans.push_back(cur);
    }
    return ans;
}

std::string Unite(Path dir) {
    std::string ans = "/";
    for (auto u : dir) {
        ans += u;
        ans += '/';
    }
    if (ans.size() > 1) {
        ans.pop_back();
    }
    return ans;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path[0] == '/') {
        current_working_dir = "/";
    }
    Path curr_dir = Split(current_working_dir);
    Path dir = Split(path);
    std::reverse(dir.begin(), dir.end());

    while (!dir.empty()) {
        std::string now = dir.back();
        dir.pop_back();

        if (now == ".") {
            continue;
        }
        if (now == "..") {
            if (!curr_dir.empty()) {
                curr_dir.pop_back();
            }
            continue;
        }
        curr_dir.push_back(now);
    }

    return Unite(curr_dir);
}