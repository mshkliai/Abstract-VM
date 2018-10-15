/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:56:00 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/15 14:56:01 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVM_H
# define AVM_H

# include "../Inc/includes.h"

# include "FlowParser.hpp"
# include "IOperand.hpp"
# include "../Classes/Operand.hpp"
# include "Reader.hpp"
# include "Lexer.hpp"
# include "Parser.hpp"
# include "Executor.hpp"

class	Avm
{
	public:

		Avm();
		Avm(std::string const & file_name);
		Avm(Avm const &);
		~Avm();

		Avm	&operator = (Avm const &obj);

		void						execution();

	private:

		int							errors;
		std::deque<IOperand*>		avm_stack;
		std::vector<std::string>	file_content;
		std::vector<t_command*>		commands;

		Reader						reader;
		Lexer						lexer;
		Parser						parser;
		Executor					executor;

		void						validation();
		void						handle_end_errors();
		void						clearContainers();
};

#endif
