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
	try {
		int32_t v = std::stoi(value, 0, 10);

		if ( v > std::numeric_limits<int8_t>::max() )
			throw Overflow8();
		else if ( v < std::numeric_limits<int8_t>::min() )
			throw Underflow8();
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-')
			std::cerr << "Underflow for int8_t" << std::endl;
		else
			std::cerr << "Overflow for int8_t" << std::endl;

		return false;
	}
	return true;
}

bool		FlowParser::check_int16(std::string const & value) const
{
	try {
		int32_t v = std::stoi(value, 0, 10);

		if ( v > std::numeric_limits<int16_t>::max() )
			throw Overflow16();
		else if ( v < std::numeric_limits<int16_t>::min() )
			throw Underflow16();
	}
	catch (std::out_of_range & e)
	{
		std::cerr << "'" << value << "'?!" << std::endl;
		if (value[0] == '-')
			std::cerr << "Underflow for int16_t" << std::endl;
		else
			std::cerr << "Overflow for int16_t" << std::endl;

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
		if (value[0] == '-')
			std::cerr << "Underflow for int32_t" << std::endl;
		else
			std::cerr << "Overflow for int32_t" << std::endl;

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
		if (value[0] == '-')
			std::cerr << "Underflow for float" << std::endl;
		else
			std::cerr << "Overflow for float" << std::endl;

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
		if (value[0] == '-')
			std::cerr << "Underflow for double" << std::endl;
		else
			std::cerr << "Overflow for double" << std::endl;

		return false;
	}
	return true;
}

/* Except Class */

FlowParser::Overflow8::Overflow8() throw()
{
	return ;
}

FlowParser::Overflow8::Overflow8(FlowParser::Overflow8 const &obj) throw()
{
	*this = obj;
}

FlowParser::Overflow8::~Overflow8() throw()
{
	return ;
}

FlowParser::Overflow8 &FlowParser::Overflow8::operator = (FlowParser::Overflow8 const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char *	FlowParser::Overflow8::what() const throw()
{
	return "Max int8_t = 127";
}

/* Except Class */

FlowParser::Underflow8::Underflow8() throw()
{
	return ;
}

FlowParser::Underflow8::Underflow8(FlowParser::Underflow8 const &obj) throw()
{
	*this = obj;
}

FlowParser::Underflow8::~Underflow8() throw()
{
	return ;
}

FlowParser::Underflow8 &FlowParser::Underflow8::operator = (FlowParser::Underflow8 const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char *	FlowParser::Underflow8::what() const throw()
{
	return "Min int8_t = -128";
}

/* Except Class */

FlowParser::Overflow16::Overflow16() throw()
{
	return ;
}

FlowParser::Overflow16::Overflow16(FlowParser::Overflow16 const &obj) throw()
{
	*this = obj;
}

FlowParser::Overflow16::~Overflow16() throw()
{
	return ;
}

FlowParser::Overflow16 &FlowParser::Overflow16::operator = (FlowParser::Overflow16 const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char *	FlowParser::Overflow16::what() const throw()
{
	return "Max int16_t = 32767";
}

/* Except Class */

FlowParser::Underflow16::Underflow16() throw()
{
	return ;
}

FlowParser::Underflow16::Underflow16(FlowParser::Underflow16 const &obj) throw()
{
	*this = obj;
}

FlowParser::Underflow16::~Underflow16() throw()
{
	return ;
}

FlowParser::Underflow16 &FlowParser::Underflow16::operator = (FlowParser::Underflow16 const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char *	FlowParser::Underflow16::what() const throw()
{
	return "Min int16_t = -32767";
}