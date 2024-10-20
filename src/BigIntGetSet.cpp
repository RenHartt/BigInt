/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BigIntGetSet.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@42angouleme.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:49:18 by bgoron            #+#    #+#             */
/*   Updated: 2024/10/20 16:02:41 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BigInt.hpp"

void BigInt::setDigits(std::vector<int> digits) { this->_digits = digits; }
void BigInt::setSign(bool sign) { this->_sign = sign; }

const std::vector<int> &BigInt::getDigits(void) const { return (this->_digits); }
bool BigInt::getSign(void) const { return (this->_sign); }
