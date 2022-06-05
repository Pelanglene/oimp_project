#pragma once

#include <unordered_map>
#include <sstream>
#include <vector>

class Poly {
public:
    Poly();
    Poly(const std::vector<std::pair<int64_t, int64_t>>& v);
    Poly(const std::vector<int64_t>& v);

    int64_t operator()(int64_t x) const;

    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;
    Poly operator-() const;
    Poly operator-(const Poly& other) const;
    Poly operator+(const Poly& other) const;
    Poly operator*(const Poly& other) const;

    Poly& operator+=(const Poly& other);
    Poly& operator-=(const Poly& other);

    friend std::ostream& operator<<(std::ostream& out, const Poly& p);

private:
    void DeleteZero();
    std::unordered_map<int64_t, int64_t> coef_;
};