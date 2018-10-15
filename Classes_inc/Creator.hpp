/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creator.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:55:55 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/15 19:55:56 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATOR_H
# define CREATOR_H

# include "../Inc/includes.h"

# include "../Classes/Operand.hpp"

class	Creator
{

	public:
		
		Creator();
		Creator(Creator const &obj);
		~Creator();

		Creator	&operator = (Creator const &);

		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	
	private:
		
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
};

#endif
