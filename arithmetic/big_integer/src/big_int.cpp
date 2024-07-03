//
// Created by Des Caldnd on 5/27/2024.
//

#include "../include/big_int.h"
#include <ranges>
#include <exception>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <not_implemented.h>

std::strong_ordering big_int::operator<=>(const big_int &other) const noexcept
{
    throw not_implemented("std::strong_ordering big_int::operator<=>(const big_int &) const noexcept", "your code should be here...");
}

std::strong_ordering big_int::compare(const big_int &other, size_t shift) const noexcept
{
    throw not_implemented("std::strong_ordering big_int::compare(const big_int &, size_t) const noexcept", "your code should be here...");
}

std::strong_ordering
big_int::compare_no_sign(const std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs,
                         size_t shift) noexcept
{
    throw not_implemented("std::strong_ordering big_int::compare_no_sign(const std::vector<unsigned int> &, const std::vector<unsigned int> &,size_t) noexcept", "your code should be here...");
}

void big_int::optimise() noexcept
{
    throw not_implemented("void big_int::optimise() noexcept", "your code should be here...");
}

big_int::big_int(const std::vector<unsigned int> &digits, bool sign)
{
    throw not_implemented("big_int::big_int(const std::vector<unsigned int> &, bool)", "your code should be here...");
}

big_int::big_int(std::vector<unsigned int> &&digits, bool sign)
{
    throw not_implemented("big_int::big_int(std::vector<unsigned int> &&, bool)", "your code should be here...");
}

big_int::operator bool()
{
    throw not_implemented("big_int::operator bool()", "your code should be here...");
}

big_int::big_int()
{
    throw not_implemented("big_int::big_int()", "your code should be here...");
}

big_int &big_int::operator++()
{
    throw not_implemented("big_int &big_int::operator++()", "your code should be here...");
}


big_int big_int::operator++(int)
{
    throw not_implemented("big_int big_int::operator++(int)", "your code should be here...");
}

big_int &big_int::operator--()
{
    throw not_implemented("big_int &big_int::operator--()", "your code should be here...");
}


big_int big_int::operator--(int)
{
    throw not_implemented("big_int big_int::operator--(int)", "your code should be here...");
}

big_int &big_int::operator+=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator+=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator-=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator-=(const big_int &)", "your code should be here...");
}

big_int big_int::operator+(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator+(const big_int &) const", "your code should be here...");
}

big_int big_int::operator-(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator-(const big_int &) const", "your code should be here...");
}

big_int big_int::operator*(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator*(const big_int &) const", "your code should be here...");
}

big_int big_int::operator/(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator/(const big_int &) const", "your code should be here...");
}

big_int big_int::operator%(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator%(const big_int &) const", "your code should be here...");
}

big_int big_int::operator&(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator&(const big_int &) const", "your code should be here...");
}

big_int big_int::operator|(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator|(const big_int &) const", "your code should be here...");
}

big_int big_int::operator^(const big_int &other) const
{
    throw not_implemented("big_int big_int::operator^(const big_int &) const", "your code should be here...");
}

big_int big_int::operator<<(size_t shift) const
{
    throw not_implemented("big_int big_int::operator<<(size_t ) const", "your code should be here...");
}

big_int big_int::operator>>(size_t shift) const
{
    throw not_implemented("big_int big_int::operator>>(size_t) const", "your code should be here...");
}

big_int &big_int::operator%=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator%=(const big_int &)", "your code should be here...");
}

big_int big_int::operator~() const
{
    throw not_implemented("big_int big_int::operator~() const", "your code should be here...");
}

big_int &big_int::operator&=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator&=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator|=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator|=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator^=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator^=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator<<=(size_t shift)
{
    throw not_implemented("big_int &big_int::operator<<=(size_t)", "your code should be here...");
}

big_int &big_int::operator>>=(size_t shift)
{
    throw not_implemented("big_int &big_int::operator>>=(size_t)", "your code should be here...");
}

big_int &big_int::plus_assign(const big_int &other, size_t shift)
{
    throw not_implemented("big_int &big_int::plus_assign(const big_int &, size_t)", "your code should be here...");
}

big_int &big_int::minus_assign(const big_int &other, size_t shift)
{
    throw not_implemented("big_int &big_int::minus_assign(const big_int &, size_t)", "your code should be here...");
}

big_int &big_int::operator*=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator*=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator/=(const big_int &other)
{
    throw not_implemented("big_int &big_int::operator/=(const big_int &)", "your code should be here...");
}

void big_int::plus_assign_no_sign(std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs, size_t shift)
{
    throw not_implemented("void big_int::plus_assign_no_sign(std::vector<unsigned int> &, const std::vector<unsigned int> &, size_t)", "your code should be here...");
}

void big_int::minus_assign_no_sign(std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs, size_t shift)
{
    throw not_implemented("void big_int::minus_assign_no_sign(std::vector<unsigned int> &, const std::vector<unsigned int> &, size_t)", "your code should be here...");
}

void big_int::minus_assign_no_sign_reverse(const std::vector<unsigned int> &lhs, std::vector<unsigned int> &rhs,
                                           size_t shift)
{
    throw not_implemented("void big_int::minus_assign_no_sign_reverse(const std::vector<unsigned int> &lhs, std::vector<unsigned int> &,size_t)", "your code should be here...");
}

bool big_int::need_karatsuba(const std::vector<unsigned int>& other) const noexcept
{
    throw not_implemented("bool big_int::need_karatsuba(const std::vector<unsigned int>&) const noexcept", "your code should be here...");
}

bool big_int::need_newton(const std::vector<unsigned int>& other) const noexcept
{
    throw not_implemented("bool big_int::need_newton(const std::vector<unsigned int>&) const noexcept", "your code should be here...");
}

void big_int::multiply_assign_no_sign(std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs) const
{
    throw not_implemented("void big_int::multiply_assign_no_sign(std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

void big_int::divide_assign_no_sign(std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs) const
{
    throw not_implemented("void big_int::divide_assign_no_sign(std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

std::vector<unsigned int>
big_int::multiply_common(const std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs) const
{
    throw not_implemented("std::vector<unsigned int>big_int::multiply_common(const std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

std::vector<unsigned int> big_int::summ_four(unsigned int a0b0, unsigned int a1b0, unsigned int a0b1, unsigned int a1b1)
{
    throw not_implemented("std::vector<unsigned int> big_int::summ_four(unsigned int, unsigned int, unsigned int, unsigned int)", "your code should be here...");
}

void big_int::move_caret(std::vector<unsigned int>& vec, unsigned int new_var)
{
    throw not_implemented("void big_int::move_caret(std::vector<unsigned int>&, unsigned int)", "your code should be here...");
}

unsigned int big_int::find_quolitent(const std::vector<unsigned int> &numerator, const std::vector<unsigned int> &denominator) const
{
    throw not_implemented("unsigned int big_int::find_quolitent(const std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

std::vector<unsigned int>
big_int::divide_common(const std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs) const
{
    throw not_implemented("std::vector<unsigned int>big_int::divide_common(const std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

big_int::big_int(const std::string &num, unsigned int radix)
{
    throw not_implemented("big_int::big_int(const std::string &, unsigned int)", "your code should be here...");
}

std::string big_int::to_string() const
{
    throw not_implemented("std::string big_int::to_string() const", "your code should be here...");
}

std::ostream &operator<<(std::ostream &stream, const big_int &value)
{
    throw not_implemented("std::ostream &operator<<(std::ostream &, const big_int &)", "your code should be here...");
}

std::istream &operator>>(std::istream &stream, big_int &value)
{
    throw not_implemented("std::istream &operator>>(std::istream &, big_int &)", "your code should be here...");
}

std::vector<unsigned int>
big_int::multiply_karatsuba(const std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs) const
{
    throw not_implemented("std::vector<unsigned int>big_int::multiply_karatsuba(const std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

std::vector<unsigned int>
big_int::divide_newton(const std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs) const
{
    throw not_implemented("std::vector<unsigned int>big_int::divide_newton(const std::vector<unsigned int> &, const std::vector<unsigned int> &) const", "your code should be here...");
}

bool big_int::operator==(const big_int &other) const noexcept
{
    throw not_implemented("bool big_int::operator==(const big_int &) const noexcept", "your code should be here...");
}

std::vector<big_int> big_int::newton_transform(const std::vector<big_int> &f)
{
    throw not_implemented("std::vector<big_int> big_int::newton_transform(const std::vector<big_int> &)", "your code should be here...");
}

std::vector<big_int> big_int::multiply_vector(const std::vector<big_int> &lhs, size_t val)
{
    throw not_implemented("std::vector<big_int> big_int::multiply_vector(const std::vector<big_int> &, size_t)", "your code should be here...");
}

void big_int::modulo_vector(std::vector<big_int> &val, size_t power)
{
    throw not_implemented("void big_int::modulo_vector(std::vector<big_int> &, size_t)", "your code should be here...");
}

std::vector<big_int> big_int::minus_vectors(const std::vector<big_int> &lhs, const std::vector<big_int> &rhs)
{
    throw not_implemented("std::vector<big_int> big_int::minus_vectors(const std::vector<big_int> &, const std::vector<big_int> &)", "your code should be here...");
}

std::vector<big_int> big_int::plus_vectors(const std::vector<big_int> &lhs, const std::vector<big_int> &rhs)
{
    throw not_implemented("std::vector<big_int> big_int::plus_vectors(const std::vector<big_int> &, const std::vector<big_int> &)", "your code should be here...");
}

std::vector<big_int> big_int::multiply_vectors(const std::vector<big_int> &lhs, const std::vector<big_int> &rhs)
{
    throw not_implemented("std::vector<big_int> big_int::multiply_vectors(const std::vector<big_int> &, const std::vector<big_int> &)", "your code should be here...");
}

template<std::integral Num>
big_int::big_int(Num d)
{
    throw not_implemented("template<std::integral Num>big_int::big_int(Num)", "your code should be here...");
}

big_int operator""_bi(unsigned long long n)
{
    throw not_implemented("big_int operator\"\"_bi(unsigned long long n)", "your code should be here...");
}