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

big_int::operator bool() const noexcept
{
    throw not_implemented("big_int::operator bool()", "your code should be here...");
}

big_int &big_int::operator++() &
{
    throw not_implemented("big_int &big_int::operator++()", "your code should be here...");
}


big_int big_int::operator++(int)
{
    throw not_implemented("big_int big_int::operator++(int)", "your code should be here...");
}

big_int &big_int::operator--() &
{
    throw not_implemented("big_int &big_int::operator--()", "your code should be here...");
}


big_int big_int::operator--(int)
{
    throw not_implemented("big_int big_int::operator--(int)", "your code should be here...");
}

big_int &big_int::operator+=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator+=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator-=(const big_int &other) &
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

big_int &big_int::operator%=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator%=(const big_int &)", "your code should be here...");
}

big_int big_int::operator~() const
{
    throw not_implemented("big_int big_int::operator~() const", "your code should be here...");
}

big_int &big_int::operator&=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator&=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator|=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator|=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator^=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator^=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator<<=(size_t shift) &
{
    throw not_implemented("big_int &big_int::operator<<=(size_t)", "your code should be here...");
}

big_int &big_int::operator>>=(size_t shift) &
{
    throw not_implemented("big_int &big_int::operator>>=(size_t)", "your code should be here...");
}

big_int &big_int::plus_assign(const big_int &other, size_t shift) &
{
    throw not_implemented("big_int &big_int::plus_assign(const big_int &, size_t)", "your code should be here...");
}

big_int &big_int::minus_assign(const big_int &other, size_t shift) &
{
    throw not_implemented("big_int &big_int::minus_assign(const big_int &, size_t)", "your code should be here...");
}

big_int &big_int::operator*=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator*=(const big_int &)", "your code should be here...");
}

big_int &big_int::operator/=(const big_int &other) &
{
    throw not_implemented("big_int &big_int::operator/=(const big_int &)", "your code should be here...");
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

bool big_int::operator==(const big_int &other) const noexcept
{
    throw not_implemented("bool big_int::operator==(const big_int &) const noexcept", "your code should be here...");
}

big_int::big_int(const std::vector<unsigned int, pp_allocator<unsigned int>> &digits, bool sign)
{
    throw not_implemented("big_int::big_int(const std::vector<unsigned int, pp_allocator<unsigned int>> &digits, bool sign)", "your code should be here...");
}

big_int::big_int(std::vector<unsigned int, pp_allocator<unsigned int>> &&digits, bool sign) noexcept
{
    throw not_implemented("big_int::big_int(std::vector<unsigned int, pp_allocator<unsigned int>> &&digits, bool sign) noexcept", "your code should be here...");
}

big_int::big_int(const std::string &num, unsigned int radix, pp_allocator<unsigned int>)
{
    throw not_implemented("big_int::big_int(const std::string &num, unsigned int radix, pp_allocator<unsigned int>)", "your code should be here...");
}

big_int::big_int(pp_allocator<unsigned int>)
{
    throw not_implemented("big_int::big_int(pp_allocator<unsigned int>)", "your code should be here...");
}

big_int &big_int::multiply_assign(const big_int &other, big_int::multiplication_rule rule) &
{
    throw not_implemented("big_int &big_int::multiply_assign(const big_int &other, big_int::multiplication_rule rule) &", "your code should be here...");
}

big_int &big_int::divide_assign(const big_int &other, big_int::division_rule rule) &
{
    throw not_implemented("big_int &big_int::divide_assign(const big_int &other, big_int::division_rule rule) &", "your code should be here...");
}

big_int &big_int::modulo_assign(const big_int &other, big_int::division_rule rule) &
{
    throw not_implemented("big_int &big_int::modulo_assign(const big_int &other, big_int::division_rule rule) &", "your code should be here...");
}

template<class alloc>
big_int::big_int(const std::vector<unsigned int, alloc> &digits, bool sign, pp_allocator<unsigned int> allocator)
{
    throw not_implemented("template<class alloc> big_int::big_int(const std::vector<unsigned int, alloc> &digits, bool sign, pp_allocator<unsigned int> allocator)", "your code should be here...");
}

template<std::integral Num>
big_int::big_int(Num d, pp_allocator<unsigned int>)
{
    throw not_implemented("template<std::integral Num>big_int::big_int(Num, pp_allocator<unsigned int>)", "your code should be here...");
}

big_int operator""_bi(unsigned long long n)
{
    throw not_implemented("big_int operator\"\"_bi(unsigned long long n)", "your code should be here...");
}