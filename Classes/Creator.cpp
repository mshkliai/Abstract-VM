/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creator.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:55:49 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/15 19:55:50 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Creator.hpp"

Creator::Creator() { }

Creator::Creator(Creator const &obj)
{
	*this = obj;
}

Creator::~Creator() { }

Creator			&Creator::operator = (Creator const &)
{
	return *this;
}

IOperand const *Creator::createOperand(eOperandType type, std::string const & value) const
{
	const IOperand* (Creator::*create_operands[5])(std::string const &) const =
	{
		&Creator::createInt8,
		&Creator::createInt16,
		&Creator::createInt32,
		&Creator::createFloat,
		&Creator::createDouble
	};

	return (this->*create_operands[type])(value);
}

/* private */

IOperand const *Creator::createInt8(std::string const & value) const
{
	return new Operand<int8_t>(static_cast<int8_t>(std::stoi(value)), Int8);
}

IOperand const *Creator::createInt16(std::string const & value) const
{
	return new Operand<int16_t>(static_cast<int16_t>(std::stoi(value)), Int16);
}

IOperand const *Creator::createInt32(std::string const & value) const
{
	return new Operand<int32_t>(static_cast<int32_t>(std::stoi(value)), Int32);
}

IOperand const *Creator::createFloat(std::string const & value) const
{
	return new Operand<float>(static_cast<float>(std::stof(value)), Float);
}

IOperand const *Creator::createDouble(std::string const & value) const
{
	return new Operand<double>(static_cast<double>(std::stod(value)), Double);
}