//
// Created by Des Caldnd on 5/27/2024.
//

#include "../include/big_int.h"
#include <ranges>

std::strong_ordering big_int::operator<=>(const big_int &other) const noexcept
{
    return compare(other, 0);
}

std::strong_ordering big_int::compare(const big_int &other, size_t shift) const noexcept
{
    if (_digits.size() == 0 && other._digits.size() == 0)
        return std::strong_ordering::equal;
    else if (_sign != other._sign)
        return _sign ? std::strong_ordering::greater : std::strong_ordering::less;
    else
    {
        auto res = compare_no_sign(_digits, other._digits, shift);

        if (_sign)
            return res;
        else
        {
            return res == std::strong_ordering::equal ? res : res == std::strong_ordering::less ? std::strong_ordering::greater : std::strong_ordering::less;
        }
    }
}

std::strong_ordering
big_int::compare_no_sign(const std::vector<unsigned int> &lhs, const std::vector<unsigned int> &rhs,
                         size_t shift) noexcept
{
    if (lhs.size() != rhs.size() + shift)
    {
        return lhs.size() <=> (rhs.size() + shift);
    } else if (lhs.size() == 0 && rhs.size() == 0)
    {
        return std::strong_ordering::equal;
    } else
    {
        auto lbeg = lhs.rbegin(), lend = lhs.rend(), rbeg = rhs.rbegin(), rend = rhs.rend();

        for(; lbeg < lend; ++lbeg, ++rbeg)
        {
            auto l = *lbeg;
            auto r = rbeg < rend ? *rbeg : 0;

            if (l != r)
                return l <=> r;
        }

        return std::strong_ordering::equal;
    }
}

void big_int::optimise() noexcept
{
    while(!_digits.empty() && _digits.back() == 0)
        _digits.pop_back();

    if (_digits.empty())
        _sign = true;
}

big_int::big_int(const std::vector<unsigned int> &digits, bool sign) : _digits(digits), _sign(sign) {}

big_int::big_int(std::vector<unsigned int> &&digits, bool sign) : _digits(std::move(digits)), _sign(sign) {}

big_int::operator bool()
{
    return !_digits.empty();
}

big_int::big_int() : _digits(), _sign(true) {}

big_int &big_int::operator++()
{
    return operator+=(1);
}


big_int big_int::operator++(int)
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

big_int &big_int::operator--()
{
    return operator-=(1);
}


big_int big_int::operator--(int)
{
    auto tmp = *this;
    --(*this);
    return tmp;
}

big_int &big_int::operator+=(const big_int &other)
{
    return plus_assign(other);
}

big_int &big_int::operator-=(const big_int &other)
{
    return minus_assign(other);
}

big_int big_int::operator+(const big_int &other) const
{
    auto tmp = *this;
    return tmp += other;
}

big_int big_int::operator-(const big_int &other) const
{
    auto tmp = *this;
    return tmp -= other;
}

big_int big_int::operator*(const big_int &other) const
{
    auto tmp = *this;
    return tmp *= other;
}

big_int big_int::operator/(const big_int &other) const
{
    auto tmp = *this;
    return tmp /= other;
}

big_int big_int::operator%(const big_int &other) const
{
    auto tmp = *this;
    return tmp %= other;
}

big_int big_int::operator&(const big_int &other) const
{
    auto tmp = *this;
    return tmp &= other;
}

big_int big_int::operator|(const big_int &other) const
{
    auto tmp = *this;
    return tmp |= other;
}

big_int big_int::operator^(const big_int &other) const
{
    auto tmp = *this;
    return tmp ^= other;
}

big_int big_int::operator<<(size_t shift) const
{
    auto tmp = *this;
    return tmp <<= shift;
}

big_int big_int::operator>>(size_t shift) const
{
    auto tmp = *this;
    return tmp >>= shift;
}

big_int &big_int::operator%=(const big_int &other)
{
    return operator-=((*this / other) * other);
}

big_int big_int::operator~() const
{
    auto res = *this;
    res._sign = !res._sign;
    for (auto& num : res._digits)
    {
        num = ~num;
    }
    res.optimise();
    return res;
}

big_int &big_int::operator&=(const big_int &other)
{
    if (!_sign && other._sign)
        _sign = true;

    for(size_t i = 0; i < _digits.size(); ++i)
        _digits[i] &= i < other._digits.size() ? other._digits[i] : 0;

    optimise();
    return *this;
}

big_int &big_int::operator|=(const big_int &other)
{
    if (_sign && !other._sign)
        _sign = false;

    if (_digits.size() < other._digits.size())
        _digits.resize(other._digits.size(), 0);

    for(size_t i = 0; i < _digits.size(); ++i)
        _digits[i] |= other._digits[i];

    optimise();
    return *this;
}

big_int &big_int::operator^=(const big_int &other)
{
    if (_sign != other._sign)
        _sign = true;
    else
        _sign = false;

    if (_digits.size() < other._digits.size())
        _digits.resize(other._digits.size(), 0);

    for(size_t i = 0; i < _digits.size(); ++i)
        _digits[i] ^= other._digits[i];

    optimise();
    return *this;
}

big_int &big_int::operator<<=(size_t shift)
{
    if (shift / (8 * sizeof(unsigned int)) > 0)
    {
        size_t n = shift / (8 * sizeof(unsigned int));

        std::vector<unsigned int> vec(n, 0);

        _digits.insert_range(_digits.begin(), vec);

        shift %= 8 * sizeof(unsigned int);
    }

    if (shift == 0)
        return *this;

    unsigned int c = 0;

    for(auto & num : _digits)
    {
        auto tmp = num;
        num = (num << shift) | c;
        c = tmp >> (8 * sizeof(unsigned int) - shift);
    }

    if (c != 0)
        _digits.push_back(c);

    optimise();
    return *this;
}

big_int &big_int::operator>>=(size_t shift)
{
    if (shift / (8 * sizeof(unsigned int)) > 0)
    {
        size_t n = shift / (8 * sizeof(unsigned int));

        if (n > _digits.size())
        {
            _sign = true;
            _digits.clear();
            return *this;
        }

        _digits.erase(_digits.begin(), _digits.begin() + n);

        shift %= 8 * sizeof(unsigned int);
    }

    if (shift == 0)
        return *this;


    unsigned int c = 0;

    for(auto& num : std::views::reverse(_digits))
    {
        auto tmp = num;
        num = (num >> shift) | c;
        c =  tmp << (8 * sizeof(unsigned int) - shift);
    }

    optimise();
    return *this;
}

big_int &big_int::plus_assign(const big_int &other, size_t shift)
{
    if (_sign == other._sign)
    {
        plus_assign_no_sign(_digits, other._digits, shift);
    } else
    {
        auto comp = compare_no_sign(_digits, other._digits, shift);
        if (comp == std::strong_ordering::equal)
        {
            _sign = true;
            _digits.clear();
        } else if (comp == std::strong_ordering::less)
        {
            _sign = !_sign;
            minus_assign_no_sign_reverse(other._digits, _digits, shift);
        } else
        {
            minus_assign_no_sign(_digits, other._digits, shift);
        }
    }

    optimise();
    return *this;
}

big_int &big_int::minus_assign(const big_int &other, size_t shift)
{
    if (_sign != other._sign)
    {
        plus_assign_no_sign(_digits, other._digits, shift);
    } else
    {
        auto comp = compare_no_sign(_digits, other._digits, shift);
        if (comp == std::strong_ordering::equal)
        {
            _sign = true;
            _digits.clear();
        } else if (comp == std::strong_ordering::less)
        {
            _sign = !_sign;
            minus_assign_no_sign_reverse(other._digits, _digits, shift);
        } else
        {
            minus_assign_no_sign(_digits, other._digits, shift);
        }
    }

    optimise();
    return *this;
}

big_int &big_int::operator*=(const big_int &other)
{
    _sign = _sign == other._sign;
    multiply_assign_no_sign(_digits, other._digits);

    optimise();
    return *this;
}

big_int &big_int::operator/=(const big_int &other)
{
    _sign = _sign == other._sign;
    divide_assign_no_sign(_digits, other._digits);

    optimise();
    return *this;
}

template<std::integral Num>
big_int::big_int(Num d) : _sign(true)
{
    if (d != 0)
    {
        if constexpr (std::signed_integral<Num>)
        {
            _sign = d >= 0;
            _digits.push_back(d >= 0 ? d : -1 * d);
        } else
        {
            _digits.push_back(d);
        }
    }
}