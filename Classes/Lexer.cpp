/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 11:55:52 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/16 11:55:53 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Lexer.hpp"

Lexer::Lexer()
{
	this->commands.push_back("push");
	this->commands.push_back("pop");
	this->commands.push_back("dump");
	this->commands.push_back("pro_dump");
	this->commands.push_back("assert");
	this->commands.push_back("add");
	this->commands.push_back("sub");
	this->commands.push_back("mul");
	this->commands.push_back("div");
	this->commands.push_back("mod");
	this->commands.push_back("power");
	this->commands.push_back("print");
	this->commands.push_back("print8");
	this->commands.push_back("print16");
	this->commands.push_back("print32");
	this->commands.push_back("printfl");
	this->commands.push_back("printd");
	this->commands.push_back("exit");

	this->operands.push_back("int8");
	this->operands.push_back("int16");
	this->operands.push_back("int32");
	this->operands.push_back("float");
	this->operands.push_back("double");
}

Lexer::Lexer(Lexer const &obj)
{
	*this = obj;
}

Lexer::~Lexer()
{
	return ;
}

Lexer 						&Lexer::operator = (Lexer const &obj)
{
	this->words = obj.words;
	this->commands = obj.commands;
	this->operands = obj.operands;
	this->value = obj.value;
	this->has_command = obj.has_command;
	this->has_operand = obj.has_operand;
	this->operand_type = obj.operand_type;
	this->command = obj.command;

	return *this;
}

/* Getters */

int							Lexer::getOperandType() const
{
	return this->operand_type;
}

int 						Lexer::getCommand() const
{
	return this->command;
}

std::string					Lexer::getValue() const
{
	return this->value;
}

/* Function */

void						Lexer::check_str(const std::string & str)
{
	this->has_command = false;
	this->has_operand = false;
	this->operand_type = -1;
	this->command = -1;
	this->value = "";

	makeWords(const_cast<char*>(str.c_str()));

	for (size_t i = 0; i < this->words.size() && is_comment(this->words[i]) == false; i++)
	{
		if (is_command(this->words[i]) == false &&
		is_operand(this->words[i]) == false &&
		is_comment(this->words[i]) == false)
		{
			throw std::logic_error("Unknown instruction");
		}
	}

	if (this->has_command == true && this->has_operand == false) {
		throw std::logic_error("Need value for command push/assert");
	}
	else if (this->has_command == false && this->has_operand == true) {
		throw std::logic_error("Need push/assert - commands for value");
	}
}

void						Lexer::check_end(bool stream, bool exit, std::string const & last_str)
{
	if (exit == false) {
		throw std::logic_error("No command 'exit'");
	}
	else if (stream == true && last_str != ";;") {
		throw std::logic_error("No ';;' from standart input");
	}
}

/* Private checkers */

bool						Lexer::is_command(std::string const & str)
{
	for (size_t i = 0; i < this->commands.size(); i++)
	{
		if (str == this->commands[i])
		{
			if (str == "assert" || str == "push") {
				this->has_command = true;
			}
			this->command = i;
			return true;
		}
	}

	return false;
}

bool						Lexer::is_operand(std::string const & str)
{
	std::string	cpy_str = str;

	if (cpy_str[cpy_str.length() - 1] != ')' || check_brackets(cpy_str) == false) {
		 return false;
	}
	
	if (cpy_str.find('(') != std::string::npos) {
		cpy_str.erase(cpy_str.find('('));
	}
	else {
		return false;
	}

	for (size_t i = 0; i < this->operands.size(); i++)
	{
		if (cpy_str == this->operands[i])
		{
			this->operand_type = i;

			check_value(str);
			this->has_operand = true;
			return true;
		}
	}

	return false;
}

bool						Lexer::is_comment(std::string const & str)
{
	std::string	cpy_str = str;

	if (cpy_str[0] == ';') {
		return true;
	}
	else
	{
		if ( cpy_str.find(';') != std::string::npos ) {
			cpy_str.erase(cpy_str.find(';'));
		}
		else
			return false;

		if (is_command(cpy_str) == false && is_operand(cpy_str) == false)
			return false;
	}

	return true;
}

bool						Lexer::check_brackets(std::string const & str)
{
	int	left = 0;
	int	right = 0;

	for (size_t i = str.find('('); i < str.length(); i++)
	{
		str[i] == '(' ? left += 1 : 0;
		str[i] == ')' ? right += 1 : 0;
	}

	if (left != 1 || right != 1) {
		return false;
	}
	if ( str.find(')') - str.find('(') == 1 ) {
		throw std::logic_error("Empty Brackets()");
	}
	return true;
}

bool						Lexer::check_value(std::string const & str)
{
	std::string	value;
	int 		i = 0;

	while (str[i] && str[i] != '(') {
		i++;
	}
	while (str[++i] && str[i] != ')') {
		value += str[i];
	}

	if ( this->operands[this->operand_type] != "float" &&
	this->operands[this->operand_type] != "double" ) {
		return is_valid_Int(value);
	}
	
	return is_valid_Float(value);
}

/* Value Checkers */

bool						Lexer::is_valid_Int(std::string const & value)
{
	size_t	i = 0;
	value[i] == '-' ? i = 1 : 0;

	for (; i < value.length(); i++)
	{
		if (isdigit(value[i]) == false) {
			throw std::logic_error("Bad int value");
		}
	}
	this->value = value;

	return true;
}

bool						Lexer::is_valid_Float(std::string const & value)
{
	int		point = 0;
	size_t	i = 0;
	value[i] == '-' ? i = 1 : 0;

	for (; i < value.length(); i++)
	{
		if ( isdigit(value[i]) == false && value[i] != '.' ) {
			throw std::logic_error("Bad value for a floating-point number");
		}
		value[i] == '.' ? point += 1 : 0;
	}

	if (point < 1) {
		throw std::logic_error("Bad value for a floating-point number");
	}
	if ( point > 1 || value[value.length() - 1] == '.' || value[0] == '.' ) {
		throw std::logic_error("Extra '.'");
	}
	this->value = value;

	return true;
}

/* Function */

void						Lexer::makeWords(char const * str)
{
	char 	*str2 = new char[strlen(str) + 1];
	strcpy(str2, str);
	char	*word = strtok(str2, " \t");

	this->words.clear();
	while (word != NULL)
	{
		this->words.push_back( static_cast<std::string>(word) );
		word = strtok(NULL, " \t");
	}
	delete [] str2;
}