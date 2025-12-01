#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

template <size_t N>
std::array<int, N> fht_polynomial(std::array<int, N> data) {
    for (size_t iter = 1; iter < N; iter *= 2) {
        for (size_t i = 0; i < N; ++i) {
            if ((i & iter) == 0) {
                size_t j = i | iter;
                data[j] = data[i] ^ data[j];
            }
        }
    }
    return data;
}

const std::vector<std::string> make_monomials(const std::string& vars) {
    size_t n_vars = vars.size();
    size_t n_monomials = (1U << n_vars);
    std::vector<std::string> res;
    res.reserve(n_monomials);

    for (size_t mask = 0; mask < n_monomials; ++mask) {
        std::string monomial;
        for (size_t i = 0; i < n_vars; ++i) {
            if ((mask >> i) & 1) {
                monomial += vars[i];
            }
        }

        if (monomial.empty()) {
            res.emplace_back("1");
        } else {
            res.emplace_back(monomial);
        }
    }
    return res;
}

template <size_t N>
std::string make_ans(const std::array<int, N>& data, const std::string& alph) {
    const std::vector<std::string> monomials = make_monomials(alph);
    std::string res;
    bool first = true;

    for (size_t i = 0; i < N; ++i) {
        if (data[i] != 0) {
            if (!first) {
                res += " \u2295 ";
            }
            res += monomials[i];
            first = false;
        }
    }
    return res;
}

template <size_t N>
std::string zhegalkin_impl(int f, const std::string& alph) {
    std::array<int, N> a{};

    for (size_t i = 0; i < N; ++i) {
        a[i] = (f >> i) & 1;
    }

    std::array<int, N> coefficients = fht_polynomial<N>(a);

    return make_ans<N>(coefficients, alph);
}

const std::string zhegalkin(int f, const std::string& alph = "xyz") {
    size_t n_vars = alph.size();
    size_t N = 1U << n_vars;

    if (N > 32) {
        throw std::runtime_error("Поддерживается до 5 переменных (N<=32).");
    }

    if (N == 1) return zhegalkin_impl<1>(f, alph);
    if (N == 2) return zhegalkin_impl<2>(f, alph);
    if (N == 4) return zhegalkin_impl<4>(f, alph);
    if (N == 8) return zhegalkin_impl<8>(f, alph);
    if (N == 16) return zhegalkin_impl<16>(f, alph);
    if (N == 32) return zhegalkin_impl<32>(f, alph);

    return "";
}

int main() {
    int f_scheme = 0b10010110;

    std::cout << zhegalkin(f_scheme, "abc") << std::endl;

    return 0;
}