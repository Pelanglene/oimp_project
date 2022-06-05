#include "poly.h"

#include <iostream>

int64_t Binpow(int64_t base, int64_t st) {
    int64_t ans = 1;
    while (st) {
        if (st & 1) {
            ans *= base;
        }
        st >>= 1;
        if (st != 0) {
            base *= base;
        }
    }
    return ans;
}

Poly::Poly() {
}

Poly::Poly(const std::vector<int64_t>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i]) {
            coef_[i] = v[i];
        }
    }
}

Poly::Poly(const std::vector<std::pair<int64_t, int64_t>>& v) {
    for (const auto& [power, cf] : v) {
        if (cf) {
            coef_[power] = cf;
        }
    }
}

int64_t Poly::operator()(int64_t x) const {
    int64_t ans = 0;
    for (const auto& [power, coef] : coef_) {
        ans += coef * Binpow(x, power);
    }
    return ans;
}

bool Poly::operator==(const Poly& other) const {
    return coef_ == other.coef_;
}

bool Poly::operator!=(const Poly& other) const {
    return coef_ != other.coef_;
}

void Poly::DeleteZero() {
    std::vector<int64_t> to_delete;
    for (auto u : coef_) {
        if (u.second == 0) {
            to_delete.push_back(u.first);
        }
    }
    for (auto u : to_delete) {
        coef_.erase(u);
    }
}

Poly Poly::operator-() const {
    Poly res = *this;
    for (auto u : res.coef_) {
        res.coef_[u.first] = -u.second;
    }
    return res;
}

Poly Poly::operator+(const Poly& other) const {
    Poly res = *this;
    for (auto u : other.coef_) {
        res.coef_[u.first] += u.second;
    }
    res.DeleteZero();
    return res;
}

Poly Poly::operator-(const Poly& other) const {
    return *this + -other;
}

Poly Poly::operator*(const Poly& other) const {
    Poly res;
    for (auto u1 : coef_) {
        for (auto u2 : other.coef_) {
            res.coef_[u1.first + u2.first] += u1.second * u2.second;
        }
    }
    res.DeleteZero();
    return res;
}

Poly& Poly::operator+=(const Poly& other) {
    *this = *this + other;
    return *this;
}

Poly& Poly::operator-=(const Poly& other) {
    *this = *this - other;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Poly& p) {
    out << "y = ";
    bool first = true;
    for (auto u : p.coef_) {
        if (!first) {
            out << " + ";
        }
        first = false;
        out << u.second;
        if (u.first != 0) {
            out << "x^" << u.first;
        }
    }
    if (p.coef_.empty()) {
        out << "0";
    }
    return out;
}