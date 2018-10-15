/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 10:48:54 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/15 10:48:58 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_H
# define OPERAND_H

# include "../Inc/includes.h"

# include "../Classes_inc/IOperand.hpp"
# include "../Classes_inc/FlowParser.hpp"

template <typename T>

class	Operand : public IOperand, public FlowParser
{

	public:
		
		Operand();

		Operand(T N, eOperandType type) : value(N), _type(type)
		{
			if (this->_type == Int8) {
				this->str = std::to_string(static_cast<int>(this->value));
			}
			else {
				this->str = std::to_string(this->value);
			}
		}

		Operand(Operand const &obj)
		{
			*this = obj;
		}

		~Operand()
		{
			return ;
		}

		Operand 	&operator = (Operand const &obj)
		{
			this->value = obj.value;

			return *this;
		}

/* Functions */

		int				getPrecision(void) const
		{
			return this->_type;
		}

		eOperandType	getType(void) const
		{
			return this->_type;
		}

		IOperand *CreateObj(double val, eOperandType const & type) const
		{
			IOperand	*new_obj;

			switch (type)
			{
				case Int8:
					new_obj = new Operand<int8_t>(static_cast<int8_t>(val), type);
					break ;
				case Int16:
					new_obj = new Operand<int16_t>(static_cast<int16_t>(val), type);
					break ;
				case Int32:
					new_obj = new Operand<int32_t>(static_cast<int32_t>(val), type);
					break ;
				case Float:
					new_obj = new Operand<float>(static_cast<float>(val), type);
					break ;
				default:
					new_obj = new Operand<double>(static_cast<double>(val), type);
			}

			return new_obj;
		}

/* Operators */

		IOperand const * operator+(IOperand const & rhs) const
		{
			double			val = std::stod(rhs.toString());
			eOperandType	type;

			type = this->_type;
			type < rhs.getType() ? type = rhs.getType() : 0;

			try
			{
			 	this->parse_flow(std::to_string(val + this->value), type);
			 	return CreateObj(val + this->value, type);
			}
			catch (std::exception & e) {
				return NULL;
			}
		}

		IOperand const * operator-(IOperand const & rhs) const
		{
			double			val = std::stod(rhs.toString());
			eOperandType	type;

			type = this->_type;
			type < rhs.getType() ? type = rhs.getType() : 0;

			try
			{
				this->parse_flow(std::to_string(this->value - val), type);
				return CreateObj(this->value - val, type);
			}
			catch (std::exception & e) {
				return NULL;
			}
		}

		IOperand const * operator*(IOperand const & rhs) const
		{
			double			val = std::stod(rhs.toString());
			eOperandType	type;

			type = this->_type;
			type < rhs.getType() ? type = rhs.getType() : 0;
			
			try
			{
				this->parse_flow(std::to_string(this->value * val), type);
				return CreateObj(this->value * val, type);
			}
			catch (std::exception & e) {
				return NULL;
			}
		}

		IOperand const * operator/(IOperand const & rhs) const
		{
			double			val = std::stod(rhs.toString());
			eOperandType	type;

			type = this->_type;
			type < rhs.getType() ? type = rhs.getType() : 0;

			if (val == 0) {
				throw DivNull();
			}
			else
			{
				try
				{
					this->parse_flow(std::to_string(this->value / val), type);
					return CreateObj(this->value / val, type);
				}
				catch (std::exception & e) {
					return NULL;
				}
			}
		}

		IOperand const * operator%(IOperand const & rhs) const
		{
			double			val = std::stod(rhs.toString());
			eOperandType	type;

			type = this->_type;
			type < rhs.getType() ? type = rhs.getType() : 0;

			if (val == 0) {
				throw ModNull();
			}
			else
			{
				try
				{
					this->parse_flow( std::to_string( std::fmod(this->value, val) ), type );
					return CreateObj( std::fmod(this->value, val), type );
				}
				catch (std::exception & e) {
					return NULL;
				}
			}
		}

/* Function */

		std::string	const & toString(void) const
		{
			return this->str;
		}

	private:

		T 					value;
		eOperandType		_type;
		std::string 		str;

/* Except Class */

		class DivNull : public std::exception
		{

			public:
			
				DivNull() throw()
				{
					return ;
				}

				DivNull(DivNull const &obj) throw()
				{
					*this = obj;
				}

				~DivNull() throw()
				{
					return ;
				}

				DivNull &operator = (DivNull const &obj) throw()
				{
					static_cast<void>(obj);

					return *this;
				}

				const char * what() const throw()
				{
					return "Division by zero";
				}
		};

/* Except Class */

		class ModNull : public std::exception
		{
		
			public:
			
				ModNull() throw()
				{
					return ;
				}

				ModNull(ModNull const &obj) throw()
				{
					*this = obj;
				}

				~ModNull() throw()
				{
					return ;
				}

				ModNull &operator = (ModNull const &obj) throw()
				{
					static_cast<void>(obj);

					return *this;
				}

				const char * what() const throw()
				{
					return "Modulo by zero";
				}
		};
};

#endif