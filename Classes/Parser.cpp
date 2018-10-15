/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 18:03:13 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/19 18:03:14 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Parser.hpp"

Parser::Parser()
{
	 this->exit = false;
}

Parser::Parser(Parser const &obj)
{
	*this = obj;
}

Parser::~Parser()
{
	return ;
}

Parser	&Parser::operator = (Parser const &obj)
{
	FlowParser::operator = (obj);
	this->exit = obj.exit;

	return *this;
}

t_command	*Parser::validate_command(Lexer const & obj)
{
	t_command	*a;

	if ( (obj.getValue().empty() == false &&
		!( this->parse_flow( obj.getValue(), static_cast<eOperandType>(obj.getOperandType()))
		|| obj.getCommand() == -1)) )
	{
		return NULL;
	}

	if (static_cast<eCommand>(obj.getCommand() == exitt)) {
		this->exit = true;
	}

	a = new t_command;
	a->name = static_cast<eCommand>(obj.getCommand());
	a->type = static_cast<eOperandType>(obj.getOperandType());
	a->value = obj.getValue();
	return a;
}

bool		Parser::getExit()
{
	return this->exit;
}