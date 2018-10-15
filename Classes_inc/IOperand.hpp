/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 18:34:20 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/14 18:34:22 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_H
# define IOPERAND_H

# include "../Inc/includes.h"

class	IOperand
{

	public:
	
		virtual int				getPrecision(void) const = 0;
		virtual eOperandType	getType(void) const = 0;

		virtual IOperand const * operator+(IOperand const & rhs) const = 0;
		virtual IOperand const * operator-(IOperand const & rhs) const = 0;
		virtual IOperand const * operator*(IOperand const & rhs) const = 0;
		virtual IOperand const * operator/(IOperand const & rhs) const = 0;
		virtual IOperand const * operator%(IOperand const & rhs) const = 0;

		virtual std::string const & toString(void) const = 0;

		virtual ~IOperand(void) {}

};

#endif