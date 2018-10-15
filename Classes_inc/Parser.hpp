/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 18:03:20 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/19 18:03:20 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../Inc/includes.h"

# include "Lexer.hpp"
# include "FlowParser.hpp"

class	Parser : public FlowParser
{
	public:
		
		Parser();
		Parser(Parser const &obj);
		~Parser();

		Parser		&operator = (Parser const &obj);

		bool		getExit();

		t_command	*validate_command(Lexer const & obj);

	private:

		bool		exit;
};

#endif
