/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 18:33:03 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/21 18:33:04 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../Inc/includes.h"

# include "Creator.hpp"

class				Executor
{

	public:
	
		Executor();
		Executor(Executor const & obj);
		~Executor();

		Executor 	&operator = (Executor const & obj);

		void		execute(t_command const &command, std::deque<IOperand*> *avm_stack);

	private:

		bool		is_exit;
		std::string	value;
		t_command	cmd;

		Creator		creator;

		void		stacker(std::deque<IOperand*> *avm_stack, IOperand *new_operand);

		void		push(std::deque<IOperand*> *avm_stack);
		void		pop(std::deque<IOperand*> *avm_stack);
		void		dump(std::deque<IOperand*> *avm_stack);
		void		pro_dump(std::deque<IOperand*> *avm_stack);
		void		assert(std::deque<IOperand*> *avm_stack);
		void		add(std::deque<IOperand*> *avm_stack);
		void		sub(std::deque<IOperand*> *avm_stack);
		void		mul(std::deque<IOperand*> *avm_stack);
		void		div(std::deque<IOperand*> *avm_stack);
		void		mod(std::deque<IOperand*> *avm_stack);
		void		power(std::deque<IOperand*> *avm_stack);
		void		print(std::deque<IOperand*> *avm_stack);
		void		print8(std::deque<IOperand*> *avm_stack);
		void		print16(std::deque<IOperand*> *avm_stack);
		void		print32(std::deque<IOperand*> *avm_stack);
		void		printfl(std::deque<IOperand*> *avm_stack);
		void		printd(std::deque<IOperand*> *avm_stack);
		void		exit(std::deque<IOperand*> *avm_stack);
};

#endif