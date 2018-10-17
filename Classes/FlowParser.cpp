/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlowParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:38:23 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/22 11:38:23 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/FlowParser.hpp"

FlowParser::FlowParser()
{
	return ;
}

FlowParser::FlowParser(FlowParser const & obj)
{
	*this = obj;
}

FlowParser::~FlowParser()
{
	return ;
}

FlowParser 	&FlowParser::operator = (FlowParser const &)
{
	return *this;
}

bool		FlowParser::parse_flow(std::string const & value, eOperandType const & type) const
{
	bool		(FlowParser::*check_type[5])(std::string const &) const = 
	{
		&FlowParser::check_int8,
		&FlowParser::check_int16,
		&FlowParser::check_int32,
		&FlowParser::check_float,
		&FlowParser::check_double
	};

	return (this->*check_type[type])(value);
}

/* Private Checkers */

bool		FlowParser::check_int8(std::string const & value) const
{
	try 
	{
		int32_t v = std::stoi(value, 0, 10);

		if ( v > std::numeric_limits<int8_t>::max() ) {
			throw std::overflow_error("Max int8_t = 127");
		}
		else if ( v < std::numeric_limits<int8_t>::min() ) {
			throw std::underflow_error("Min int8_t = -128");
		}
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-') {
			std::cerr << "Underflow for int8_t" << std::endl;
		}
		else {
			std::cerr << "Overflow for int8_t" << std::endl;
		}

		return false;
	}
	return true;
}

bool		FlowParser::check_int16(std::string const & value) const
{
	try {
		int32_t v = std::stoi(value, 0, 10);

		if ( v > std::numeric_limits<int16_t>::max() ) {
			throw std::overflow_error("Max int16_t = 32767");
		}
		else if ( v < std::numeric_limits<int16_t>::min() ) {
			throw std::underflow_error("Min int16_t = -32767");
		}
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-') {
			std::cerr << "Underflow for int16_t" << std::endl;
		}
		else {
			std::cerr << "Overflow for int16_t" << std::endl;
		}

		return false;
	}
	return true;
}

bool		FlowParser::check_int32(std::string const & value) const
{
	try {
		std::stoi(value, 0, 10);
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-') {
			std::cerr << "Underflow for int32_t" << std::endl;
		}
		else {
			std::cerr << "Overflow for int32_t" << std::endl;
		}

		return false;
	}
	return true;
}

bool		FlowParser::check_float(std::string const & value) const
{
	try {
		std::stof(value, 0);
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-') {
			std::cerr << "Underflow for float" << std::endl;
		}
		else {
			std::cerr << "Overflow for float" << std::endl;
		}

		return false;
	}
	return true;
}

bool		FlowParser::check_double(std::string const & value) const
{
	try {
		std::stod(value, 0);
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-') {
			std::cerr << "Underflow for double" << std::endl;
		}
		else {
			std::cerr << "Overflow for double" << std::endl;
		}

		return false;
	}
	return true;
}