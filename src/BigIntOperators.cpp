/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigIntOperators.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:36:19 by bgoron            #+#    #+#             */
/*   Updated: 2024/10/20 20:14:29 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"
#include <stdexcept>

BigInt &BigInt::operator=(const BigInt &other)
{
	if (this != &other)
	{
		this->_digits = other._digits;
		this->_sign = other._sign;
	}

	return (*this);
}

BigInt BigInt::operator+(const BigInt &other) const
{
    BigInt result = *this;
    result += other;
    
	return (result);
}

BigInt BigInt::operator-(const BigInt &other) const
{
    BigInt result = *this;
    result -= other;
    
	return (result);
}

BigInt BigInt::operator*(const BigInt &other) const
{
    BigInt result = *this;
    result *= other;
    
	return (result);
}

BigInt BigInt::operator/(const BigInt &other) const
{
    BigInt result = *this;
    result /= other;
    
	return (result);
}

BigInt BigInt::operator%(const BigInt &other) const
{
    BigInt result = *this;
    result %= other;
    
	return (result);
}

BigInt &BigInt::operator+=(const BigInt &other)
{
    int carry = 0;
    size_t maxSize = std::max(this->_digits.size(), other._digits.size());
    this->_digits.resize(maxSize, 0);

    for (size_t i = 0; i < maxSize; ++i)
    {
        int sum = this->_digits[i] + (i < other._digits.size() ? other._digits[i] : 0) + carry;
        carry = sum / 1000000000;
        this->_digits[i] = sum % 1000000000;
    }

    if (carry != 0)
    {
        this->_digits.push_back(carry);
    }

    return (*this);
}

BigInt &BigInt::operator-=(const BigInt &other)
{
    int borrow = 0;
    size_t maxSize = std::max(this->_digits.size(), other._digits.size());
    this->_digits.resize(maxSize, 0);

    for (size_t i = 0; i < maxSize; ++i)
    {
        int sub = this->_digits[i] - (i < other._digits.size() ? other._digits[i] : 0) - borrow;
        if (sub < 0)
        {
            sub += 1000000000;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        this->_digits[i] = sub;
    }

    while (this->_digits.size() > 1 && this->_digits.back() == 0)
    {
        this->_digits.pop_back();
    }

    return (*this);
}

BigInt &BigInt::operator*=(const BigInt &other)
{
    std::vector<int> result(this->_digits.size() + other._digits.size(), 0);

    for (size_t i = 0; i < this->_digits.size(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < other._digits.size() || carry != 0; ++j)
        {
            long long mul = result[i + j] 
				+ static_cast<long long>(this->_digits[i]) 
				* (j < other._digits.size() ? other._digits[j] : 0) 
				* + carry;
            result[i + j] = mul % 1000000000;
            carry = mul / 1000000000;
        }
    }

    while (result.size() > 1 && result.back() == 0)
    {
        result.pop_back();
    }

    this->_digits = result;

    return (*this);
}

BigInt &BigInt::operator/=(const BigInt &other)
{
    if (other == BigInt(0))
    {
        throw std::runtime_error("Division by zero");
    }

    BigInt dividend = *this;
    BigInt result;
    BigInt current;

    for (int i = this->_digits.size() - 1; i >= 0; --i)
    {
        current._digits.insert(current._digits.begin(), dividend._digits[i]);
        int left = 0, right = 1000000000, quotientDigit = 0;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            BigInt midValue = other * BigInt(mid);

            if (midValue <= current)
            {
                quotientDigit = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        result._digits.insert(result._digits.begin(), quotientDigit);
        current -= other * BigInt(quotientDigit);
    }

    while (result._digits.size() > 1 && result._digits.back() == 0)
    {
        result._digits.pop_back();
    }

    *this = result;

    return (*this);
}

BigInt &BigInt::operator%=(const BigInt &other)
{
    if (other == BigInt(0))
    {
        throw std::runtime_error("Modulo by zero");
    }

    BigInt dividend = *this;
    BigInt current;

    for (int i = this->_digits.size() - 1; i >= 0; --i)
    {
        current._digits.insert(current._digits.begin(), dividend._digits[i]);

        int left = 0, right = 1000000000, quotientDigit = 0;

        while (left <= right)
        {
            int mid = (left + right) / 2;
            BigInt midValue = other * BigInt(mid);

            if (midValue <= current)
            {
                quotientDigit = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        current -= other * BigInt(quotientDigit);
    }

    *this = current;

    while (this->_digits.size() > 1 && this->_digits.back() == 0)
    {
        this->_digits.pop_back();
    }

    return (*this);
}

bool BigInt::operator==(const BigInt &other) const
{
    return (this->_sign == other._sign && this->_digits == other._digits);
}

bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}

bool BigInt::operator>(const BigInt &other) const
{
    if (this->_sign != other._sign)
	{
        return (this->_sign);
	}

    if (this->_digits.size() != other._digits.size())
    {
        return ((this->_sign) ? (this->_digits.size() > other._digits.size())
                             : (this->_digits.size() < other._digits.size()));
    }

    for (size_t i = this->_digits.size(); i > 0; --i)
    {
        if (this->_digits[i - 1] != other._digits[i - 1])
        {
            return ((this->_sign) ? (this->_digits[i - 1] > other._digits[i - 1])
                                 : (this->_digits[i - 1] < other._digits[i - 1]));
        }
    }

    return (false);
}

bool BigInt::operator<(const BigInt &other) const
{
    if (this->_sign != other._sign)
	{
        return (!this->_sign);
	}

    if (this->_digits.size() != other._digits.size())
    {
        return ((this->_sign) ? (this->_digits.size() < other._digits.size())
                             : (this->_digits.size() > other._digits.size()));
    }

    for (size_t i = this->_digits.size(); i > 0; --i)
    {
        if (this->_digits[i - 1] != other._digits[i - 1])
        {
            return ((this->_sign) ? (this->_digits[i - 1] < other._digits[i - 1])
                                 : (this->_digits[i - 1] > other._digits[i - 1]));
        }
    }

    return (false);
}

bool BigInt::operator>=(const BigInt &other) const
{
    return !(*this < other);
}

bool BigInt::operator<=(const BigInt &other) const
{
    return !(*this > other);
}
