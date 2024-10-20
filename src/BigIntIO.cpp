/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigIntIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:43:00 by bgoron            #+#    #+#             */
/*   Updated: 2024/10/20 16:04:53 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"
#include <string>
#include <iomanip>
#include <iostream>

std::ostream &operator<<(std::ostream &os, const BigInt &value)
{
    if (!value.getSign())
	{
        os << '-';
    }

    const std::vector<int> &digits = value.getDigits();

    os << digits.back();

    for (int i = digits.size() - 2; i >= 0; --i)
	{
        os << std::setw(9) << std::setfill('0') << digits[i];
    }

    return (os);
}

std::istream &operator>>(std::istream &is, BigInt &value)
{
    std::string input;
    is >> input;
    value = BigInt(input);

	return (is);
}
