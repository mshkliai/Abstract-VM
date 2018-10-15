/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FlowParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 11:38:28 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/22 11:38:29 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOWPARSER_H
# define FLOWPARSER_H

# include "../Inc/includes.h"

class 	FlowParser
{

	public:
		
		FlowParser();
		FlowParser(FlowParser const & obj);
		~FlowParser();

		FlowParser	&operator = (FlowParser const &);

		bool		parse_flow(std::string const & value, eOperandType const & type) const;

	private:

		bool		check_int8(std::string const & value) const;
		bool		check_int16(std::string const & value) const;
		bool		check_int32(std::string const & value) const;
		bool		check_float(std::string const & value) const;
		bool		check_double(std::string const & value) const;

		class Overflow8 : public std::exception
		{
			public:

				Overflow8() throw();
				Overflow8(Overflow8 const &obj) throw();
				~Overflow8() throw();

				Overflow8	&operator = (Overflow8 const &obj) throw();

				virtual const char * what() const throw(); 
			
		};

		class Underflow8 : public std::exception
		{
			public:

				Underflow8() throw();
				Underflow8(Underflow8 const &obj) throw();
				~Underflow8() throw();

				Underflow8	&operator = (Underflow8 const &obj) throw();

				virtual const char * what() const throw(); 
			
		};

		class Overflow16 : public std::exception
		{
			public:

				Overflow16() throw();
				Overflow16(Overflow16 const &obj) throw();
				~Overflow16() throw();

				Overflow16	&operator = (Overflow16 const &obj) throw();

				virtual const char * what() const throw(); 
			
		};

		class Underflow16 : public std::exception
		{
			public:

				Underflow16() throw();
				Underflow16(Underflow16 const &obj) throw();
				~Underflow16() throw();

				Underflow16	&operator = (Underflow16 const &obj) throw();

				virtual const char * what() const throw(); 
			
		};
};

#endif
