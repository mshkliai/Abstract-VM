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
};

#endif
