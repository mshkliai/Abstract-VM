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

/* Exception Classes */

		class UnknownInsruction : public std::exception
		{

			public:
				
				UnknownInsruction() throw();
				UnknownInsruction(UnknownInsruction const &obj) throw();
				~UnknownInsruction() throw();

				UnknownInsruction &operator = (UnknownInsruction const &obj) throw();

				virtual const char * what() const throw();
				
		};

		class NoOperand : public std::exception
		{

			public:
				
				NoOperand() throw();
				NoOperand(NoOperand const &obj) throw();
				~NoOperand() throw();

				NoOperand &operator = (NoOperand const &obj) throw();

				virtual const char * what() const throw();
				
		};

		class NoCommand : public std::exception
		{

			public:
				
				NoCommand() throw();
				NoCommand(NoCommand const &obj) throw();
				~NoCommand() throw();

				NoCommand &operator = (NoCommand const &obj) throw();

				virtual const char * what() const throw();
				
		};

		class EmptyBrackets : public std::exception
		{

			public:
				
				EmptyBrackets() throw();
				EmptyBrackets(EmptyBrackets const &obj) throw();
				~EmptyBrackets() throw();

				EmptyBrackets &operator = (EmptyBrackets const &obj) throw();

				virtual const char * what() const throw();	
		};

		class BadInt : public std::exception
		{

			public:
				
				BadInt() throw();
				BadInt(BadInt const &obj) throw();
				~BadInt() throw();

				BadInt &operator = (BadInt const &obj) throw();

				virtual const char * what() const throw();	
		};

		class BadFloatVal : public std::exception
		{

			public:
				
				BadFloatVal() throw();
				BadFloatVal(BadFloatVal const &obj) throw();
				~BadFloatVal() throw();

				BadFloatVal &operator = (BadFloatVal const &obj) throw();

				virtual const char * what() const throw();	
		};

		class ExtraPoints : public std::exception
		{

			public:
				
				ExtraPoints() throw();
				ExtraPoints(ExtraPoints const &obj) throw();
				~ExtraPoints() throw();

				ExtraPoints &operator = (ExtraPoints const &obj) throw();

				virtual const char * what() const throw();	
		};

		class NoExit : public std::exception
		{

			public:
				
				NoExit() throw();
				NoExit(NoExit const &obj) throw();
				~NoExit() throw();

				NoExit &operator = (NoExit const &obj) throw();

				virtual const char * what() const throw();	
		};

		class NoExitCin : public std::exception
		{

			public:
				
				NoExitCin() throw();
				NoExitCin(NoExitCin const &obj) throw();
				~NoExitCin() throw();

				NoExitCin &operator = (NoExitCin const &obj) throw();

				virtual const char * what() const throw();	
		};
};

#endif
