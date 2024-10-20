/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigInt.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:08:04 by bgoron            #+#    #+#             */
/*   Updated: 2024/10/20 20:14:05 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <string>

class BigInt
{
	public:
		BigInt();
		BigInt(int value);
		BigInt(const std::string &value);
		BigInt(const BigInt &other);
		~BigInt();

		BigInt& operator=(const BigInt &other);

		BigInt operator+(const BigInt &other) const;
		BigInt operator-(const BigInt &other) const;
		BigInt operator*(const BigInt &other) const;
		BigInt operator/(const BigInt &other) const;
		BigInt operator%(const BigInt &other) const;
		
		BigInt& operator+=(const BigInt &other);
		BigInt& operator-=(const BigInt &other);
		BigInt& operator*=(const BigInt &other);
		BigInt& operator/=(const BigInt &other);
		BigInt& operator%=(const BigInt &other);
		
		bool operator==(const BigInt &other) const;
		bool operator!=(const BigInt &other) const;
		bool operator>(const BigInt &other) const;
		bool operator<(const BigInt &other) const;
		bool operator>=(const BigInt &other) const;
		bool operator<=(const BigInt &other) const;

		void setDigits(std::vector<int> digits);
		void setSign(bool sign);

		const std::vector<int> &getDigits(void) const;
		bool getSign(void) const;

	private:
		std::vector<int> _digits;
		bool _sign;
};

std::ostream &operator<<(std::ostream &os, const BigInt &value);
std::istream &operator>>(std::istream &is, BigInt &value);
