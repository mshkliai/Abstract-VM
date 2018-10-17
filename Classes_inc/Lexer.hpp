/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 11:55:57 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/16 11:55:58 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../Inc/includes.h"

class			Lexer
{

	public:
	
		Lexer();
		Lexer(Lexer const &obj);
		~Lexer();

		Lexer						&operator = (Lexer const &obj);

		void						check_str(const std::string & str);
		void						check_end(bool stream, bool exit, std::string const & last_str);

/* Getters */

		int 						getOperandType() const;
		int 						getCommand() const;
		std::string 				getValue() const;

	private:

		std::vector<std::string>	words;
		std::vector<std::string>	commands;
		std::vector<std::string>	operands;
		std::string					value;
		bool 						has_command;
		bool						has_operand;
		int 						operand_type;
		int 						command;

		bool						is_command(std::string const & str);
		bool						is_operand(std::string const & str);
		bool						is_comment(std::string const & str);
		bool						check_brackets(std::string const & str);
		bool						check_value(std::string const & str);
		bool						is_valid_Int(std::string const & value);
		bool						is_valid_Float(std::string const & value);

/* Helper */

		void						makeWords(char const * str);
};

#endif
