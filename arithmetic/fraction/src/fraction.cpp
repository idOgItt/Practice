#include "../include/fraction.h"

fraction::fraction(
    big_int &&numerator,
    big_int &&denominator):
        _numerator(numerator),
        _denominator(denominator)
{
    throw not_implemented("fraction::fraction(big_integer &&, big_integer &&)", "your code should be here...");
}

fraction &fraction::operator+=(
    fraction const &other)
{
    throw not_implemented("fraction &fraction::operator+=(fraction const &)", "your code should be here...");
}

fraction fraction::operator+(
    fraction const &other) const
{
    throw not_implemented("fraction fraction::operator+(fraction const &) const", "your code should be here...");
}

fraction &fraction::operator-=(
    fraction const &other)
{
    throw not_implemented("fraction &fraction::operator-=(fraction const &)", "your code should be here...");
}

fraction fraction::operator-(
    fraction const &other) const
{
    throw not_implemented("fraction fraction::operator-(fraction const &) const", "your code should be here...");
}

fraction &fraction::operator*=(
    fraction const &other)
{
    throw not_implemented("fraction &fraction::operator*=(fraction const &)", "your code should be here...");
}

fraction fraction::operator*(
    fraction const &other) const
{
    throw not_implemented("fraction fraction::operator*(fraction const &) const", "your code should be here...");
}

fraction &fraction::operator/=(
    fraction const &other)
{
    throw not_implemented("fraction &fraction::operator/=(fraction const &)", "your code should be here...");
}

fraction fraction::operator/(
    fraction const &other) const
{
    throw not_implemented("fraction fraction::operator/(fraction const &) const", "your code should be here...");
}

bool fraction::operator==(
    fraction const &other) const
{
    throw not_implemented("bool fraction::operator==(fraction const &) const", "your code should be here...");
}

bool fraction::operator!=(
    fraction const &other) const
{
    throw not_implemented("bool fraction::operator!=(fraction const &) const", "your code should be here...");
}

bool fraction::operator>=(
    fraction const &other) const
{
    throw not_implemented("bool fraction::operator>=(fraction const &) const", "your code should be here...");
}

bool fraction::operator>(
    fraction const &other) const
{
    throw not_implemented("bool fraction::operator>(fraction const &) const", "your code should be here...");
}

bool fraction::operator<=(
    fraction const &other) const
{
    throw not_implemented("bool fraction::operator<=(fraction const &) const", "your code should be here...");
}

bool fraction::operator<(
    fraction const &other) const
{
    throw not_implemented("bool fraction::operator<(fraction const &) const", "your code should be here...");
}

std::ostream &operator<<(
    std::ostream &stream,
    fraction const &obj)
{
    throw not_implemented("std::ostream &operator<<(std::ostream &, fraction const &)", "your code should be here...");
}

std::istream &operator>>(
    std::istream &stream,
    fraction &obj)
{
    throw not_implemented("std::istream &operator>>(std::istream &, fraction &)", "your code should be here...");
}

fraction fraction::sin(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::sin(fraction const &) const", "your code should be here...");
}

fraction fraction::cos(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::cos(fraction const &) const", "your code should be here...");
}

fraction fraction::tg(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::tg(fraction const &) const", "your code should be here...");
}

fraction fraction::ctg(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::ctg(fraction const &) const", "your code should be here...");
}

fraction fraction::sec(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::sec(fraction const &) const", "your code should be here...");
}

fraction fraction::cosec(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::cosec(fraction const &) const", "your code should be here...");
}

fraction fraction::arcsin(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::arcsin(fraction const &) const", "your code should be here...");
}

fraction fraction::arccos(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::arccos(fraction const &) const", "your code should be here...");
}

fraction fraction::arctg(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::arctg(fraction const &) const", "your code should be here...");
}

fraction fraction::arcctg(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::arcctg(fraction const &) const", "your code should be here...");
}

fraction fraction::arcsec(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::arcsec(fraction const &) const", "your code should be here...");
}

fraction fraction::arccosec(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::arccosec(fraction const &) const", "your code should be here...");
}

fraction fraction::pow(
    size_t degree) const
{
    throw not_implemented("fraction fraction::pow(size_t) const", "your code should be here...");
}

fraction fraction::root(
    size_t degree,
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::root(size_t, fraction const &) const", "your code should be here...");
}

fraction fraction::log2(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::log2(fraction const &) const", "your code should be here...");
}

fraction fraction::ln(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::ln(fraction const &) const", "your code should be here...");
}

fraction fraction::lg(
    fraction const &epsilon) const
{
    throw not_implemented("fraction fraction::lg(fraction const &) const", "your code should be here...");
}