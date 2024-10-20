/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigIntConstructors.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:18:02 by bgoron            #+#    #+#             */
/*   Updated: 2024/10/20 16:51:33 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"
#include <cstdlib>
#include <vector>

BigInt::BigInt(): _digits(0), _sign(true) {}

BigInt::BigInt(int value)
{
    this->_sign = (value >= 0);
    this->_digits.push_back(std::abs(value));
}

BigInt::BigInt(const std::string &value)
{
    _sign = (value[0] != '-');
    __int128 start = _sign ? 0 : 1;

    for (__int128 i = value.size(); i > start; i -= 9)
    {
        __int128 end = i;
        __int128 begin = (i < 9 + start) ? start : i - 9;
        _digits.push_back(std::atoi(value.substr(begin, end - begin).c_str()));
    }
}

BigInt::BigInt(const BigInt &other): _digits(other._digits), _sign(other._sign) {}

BigInt::~BigInt() {}
