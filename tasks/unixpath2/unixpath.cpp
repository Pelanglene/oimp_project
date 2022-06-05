#include "unixpath.h"

//#include "iostream"

std::vector<std::string> UnixPath::StrToPath(const std::string& s) const {
    std::string buff;
    std::vector<std::string> ans;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '/') {
            if (!buff.empty()) {
                ans.push_back(buff);
                buff.clear();
            }
        } else {
            buff += s[i];
        }
    }
    if (!buff.empty()) {
        ans.push_back(buff);
    }
    return ans;
}

std::vector<std::string> UnixPath::Normalize(const std::vector<std::string>& v) const {
    std::vector<std::string> ans;
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == "..") {
            if (!ans.empty()) {
                ans.pop_back();
            }
        } else {
            if (v[i] != ".") {
                ans.push_back(v[i]);
            }
        }
    }
    return ans;
}

UnixPath::UnixPath(std::string_view bebra) {
    std::string initial_dir = static_cast<std::string>(bebra);
    initial_directory_ = Normalize(StrToPath(initial_dir));
    current_directory_ = initial_directory_;

    /*std::cout << "------\n";
    for (auto u: initial_directory_) {
        std::cout << u << " ";
    }
    std::cout << "\n------------\n";*/
}

void UnixPath::ChangeDirectory(std::string_view bebra) {
    std::string path = static_cast<std::string>(bebra);
    const std::vector<std::string> rel_path = StrToPath(path);
    if (path[0] == '/') {
        current_directory_ = Normalize(rel_path);
    } else {
        for (auto& u : rel_path) {
            if (u == "..") {
                if (!current_directory_.empty()) {
                    current_directory_.pop_back();
                }
            } else {
                if (u != ".") {
                    current_directory_.push_back(u);
                }
            }
        }
    }
    /*std::cout << "------\n";
    for (auto u: current_directory_) {
        std::cout << u << " ";
    }
    std::cout << "\n------------\n";*/
}

std::string UnixPath::PathToStr(const std::vector<std::string>& path) const {
    std::string ans;
    for (size_t i = 0; i < path.size(); ++i) {
        ans += path[i];
        if (i + 1 != path.size()) {
            ans += '/';
        }
    }
    return ans;
}

std::string UnixPath::GetAbsolutePath() const {
    return "/" + PathToStr(current_directory_);
}

std::string UnixPath::GetRelativePath() const {
    std::vector<std::string> path;
    std::string ans;
    size_t i = 0;
    /*std::cout << "~~~~~~~~~~~~~~~~`\n";
    for (auto u: initial_directory_) {
        std::cout << u << " ";
    }
    std::cout << "\n-\n";
    for (auto u: current_directory_) {
        std::cout << u << " ";
    }
    std::cout << "\n~~~~~~~~~~~~~~~~~~\n"; */
    while (i < initial_directory_.size() && i < current_directory_.size() &&
           initial_directory_[i] == current_directory_[i]) {
        ++i;
    }
    int count = initial_directory_.size() - i;
    // std::cout << count << "!!!!\n";
    while (count-- > 0) {
        path.push_back("..");
    }
    for (; i < current_directory_.size(); ++i) {
        path.push_back(current_directory_[i]);
    }
    ans = PathToStr(path);
    if (ans.empty()) {
        ans = ".";
    } else {
        if (!path.empty() && path[0] != "..") {
            ans = "./" + ans;
        }
    }
    return ans;
}
