#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;

private:
    std::vector<std::string> initial_directory_;
    std::vector<std::string> current_directory_;

    std::vector<std::string> StrToPath(const std::string& s) const;
    std::vector<std::string> Normalize(const std::vector<std::string>& v) const;
    std::string PathToStr(const std::vector<std::string>& path) const;
};
