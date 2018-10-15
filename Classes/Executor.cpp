/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 18:33:07 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/21 18:33:07 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Executor.hpp"

Executor::Executor()
{
	this->is_exit = false;
}

Executor::Executor(Executor const & obj)
{
	*this = obj;
}

Executor::~Executor() {}

Executor &Executor::operator = (Executor const & obj)
{
	this->is_exit = obj.is_exit;
	this->value = obj.value;
	this->cmd = obj.cmd;
	this->creator = obj.creator;

	return *this;
}

void	Executor::execute(t_command const &command, std::deque<IOperand*> *avm_stack)
{
	if (command.name < 0) {
		return ;
	}
	if (this->is_exit == true)
	{
		throw AfterExit();
		return ;
	}

	this->cmd = command;
	void (Executor::*executor[18])(std::deque<IOperand*> *) =
	{
		&Executor::push,
		&Executor::pop,
		&Executor::dump,
		&Executor::pro_dump,
		&Executor::assert,
		&Executor::add,
		&Executor::sub,
		&Executor::mul,
		&Executor::div,
		&Executor::mod,
		&Executor::power,
		&Executor::print,
		&Executor::print8,
		&Executor::print16,
		&Executor::print32,
		&Executor::printfl,
		&Executor::printd,
		&Executor::exit
	};
	(this->*executor[command.name])(avm_stack);
}

/* Stacker */

void	Executor::stacker(std::deque<IOperand*> *avm_stack, IOperand *new_operand)
{
	if (new_operand == NULL)
	{
		(*avm_stack)[1]->toString()[0] == '-' ?
		throw UnderflowCommand() : throw OverflowCommand();
	}
	else
	{
		delete (*avm_stack)[0];
		delete (*avm_stack)[1];
		avm_stack->pop_front();
		avm_stack->pop_front();
		avm_stack->push_front(new_operand);
	}
}

/* Commands */

void	Executor::push(std::deque<IOperand*> *avm_stack)
{
	IOperand const *new_operand = this->creator.createOperand(this->cmd.type, this->cmd.value);

	avm_stack->push_front(const_cast<IOperand*>(new_operand));
}

void	Executor::pop(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() == 0) {
		throw CommandOnEmptyStack();
	}
	else {
		avm_stack->pop_front();
	}
}

void	Executor::dump(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++) {
	 	std::cout << (*avm_stack)[i]->toString() << std::endl;
	}
}

void	Executor::pro_dump(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++)
	{
	 	std::cout << (*avm_stack)[i]->toString() << " -> ";
	 	switch ((*avm_stack)[i]->getType())
	 	{
	 		case Int8:
	 			std::cout << GREEN << "int8";
	 			break;
	 		case Int16:
	 			std::cout << GREEN << "int16";
	 			break;
	 		case Int32:
	 			std::cout << GREEN << "int32";
	 			break;
	 		case Float:
	 			std::cout << PURPLE << "float";
	 			break;
	 		default:
	 			std::cout << PURPLE << "double";
	 	}
	 	std::cout << END << std::endl;
	}
}

void	Executor::assert(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() == 0) {
		throw CommandOnEmptyStack();
	}
	else if (std::stof( (*avm_stack)[0]->toString() ) != std::stof(this->cmd.value) ||
			(*avm_stack)[0]->getType() != this->cmd.type)
	{
		throw FalseAssert();
	}
}

/* Calcs */

void	Executor::add(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() < 2) {
		throw LowStack();
	}
	else
	{
		IOperand const *new_operand = *(*avm_stack)[0] + *(*avm_stack)[1];

		this->stacker(avm_stack, const_cast<IOperand*>(new_operand));
	}
}

void	Executor::sub(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() < 2) {
		throw LowStack();
	}
	else
	{
		IOperand const *new_operand = *(*avm_stack)[0] - *(*avm_stack)[1];

		this->stacker(avm_stack, const_cast<IOperand*>(new_operand));
	}
}

void	Executor::mul(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() < 2) {
		throw LowStack();
	}
	else
	{
		IOperand const *new_operand = (*(*avm_stack)[0]) * (*(*avm_stack)[1]);

		this->stacker(avm_stack, const_cast<IOperand*>(new_operand));
	}
}

void	Executor::div(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() < 2) {
		throw LowStack();
	}
	else
	{
		IOperand const *new_operand = *(*avm_stack)[0] / *(*avm_stack)[1];

		this->stacker(avm_stack, const_cast<IOperand*>(new_operand));
	}
}

void	Executor::mod(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() < 2) {
		throw LowStack();
	}
	else
	{
		IOperand const *new_operand = *(*avm_stack)[0] % *(*avm_stack)[1];

		this->stacker(avm_stack, const_cast<IOperand*>(new_operand));
	}
}

void	Executor::power(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() < 2) {
		throw LowStack();
	}
	else if ((*avm_stack)[0]->getType() != Double &&
		(*avm_stack)[1]->getType() != Double)
		throw NoDouble();
	else 
	{

		IOperand const	*new_operand;
		double			res;
		
		res = pow( std::stod((*avm_stack)[0]->toString()),std::stod((*avm_stack)[1]->toString()) );
		new_operand = creator.createOperand(Double, std::to_string(res));
		this->stacker(avm_stack, const_cast<IOperand*>(new_operand));
	}
}

/* Simple */

void	Executor::print(std::deque<IOperand*> *avm_stack)
{
	if (avm_stack->size() == 0) {
		throw CommandOnEmptyStack();
	}
	else if ((*avm_stack)[0]->getType() != Int8) {
		throw FalsePrint();
	}
	else {
		std::cout << static_cast<int8_t>(std::stoi((*avm_stack)[0]->toString()))
			<< std::endl;
	}
}

void	Executor::print8(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++) {
		if ((*avm_stack)[i]->getType() == Int8) {
	 		std::cout << (*avm_stack)[i]->toString() << std::endl;
		}
	}
}

void	Executor::print16(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++) {
		if ((*avm_stack)[i]->getType() == Int16) {
	 		std::cout << (*avm_stack)[i]->toString() << std::endl;
		}
	}
}

void	Executor::print32(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++) {
		if ((*avm_stack)[i]->getType() == Int32) {
	 		std::cout << (*avm_stack)[i]->toString() << std::endl;
		}
	}
}

void	Executor::printfl(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++) {
		if ((*avm_stack)[i]->getType() == Float) {
	 		std::cout << (*avm_stack)[i]->toString() << std::endl;
		}
	}
}

void	Executor::printd(std::deque<IOperand*> *avm_stack)
{
	for (size_t i = 0; i < avm_stack->size(); i++) {
		if ((*avm_stack)[i]->getType() == Double) {
	 		std::cout << (*avm_stack)[i]->toString() << std::endl;
		}
	}
}

void	Executor::exit(std::deque<IOperand*> *avm_stack)
{
	static_cast<void>(avm_stack);
	this->is_exit = true;
}

/* Except Class */

Executor::CommandOnEmptyStack::CommandOnEmptyStack() throw()
{
	return ;
}

Executor::CommandOnEmptyStack::CommandOnEmptyStack(Executor::CommandOnEmptyStack const &obj) throw()
{
	*this = obj;
}

Executor::CommandOnEmptyStack::~CommandOnEmptyStack() throw()
{
	return ;
}

Executor::CommandOnEmptyStack	&Executor::CommandOnEmptyStack::operator = (Executor::CommandOnEmptyStack const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char 	*Executor::CommandOnEmptyStack::what() const throw()
{
	return "Calling command on empty stack";
}

/* Except Class */

Executor::FalseAssert::FalseAssert() throw()
{
	return ;
}

Executor::FalseAssert::FalseAssert(Executor::FalseAssert const &obj) throw()
{
	*this = obj;
}

Executor::FalseAssert::~FalseAssert() throw()
{
	return ;
}

Executor::FalseAssert	&Executor::FalseAssert::operator = (Executor::FalseAssert const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char 	*Executor::FalseAssert::what() const throw()
{
	return "An assert instruction is not true";
}

/* Except Class */

Executor::FalsePrint::FalsePrint() throw()
{
	return ;
}

Executor::FalsePrint::FalsePrint(Executor::FalsePrint const &obj) throw()
{
	*this = obj;
}

Executor::FalsePrint::~FalsePrint() throw()
{
	return ;
}

Executor::FalsePrint	&Executor::FalsePrint::operator = (Executor::FalsePrint const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char 	*Executor::FalsePrint::what() const throw()
{
	return "Value in top of stack isn't Int8";
}

/* Except Class */

Executor::LowStack::LowStack() throw()
{
	return ;
}

Executor::LowStack::LowStack(Executor::LowStack const &obj) throw()
{
	*this = obj;
}

Executor::LowStack::~LowStack() throw()
{
	return ;
}

Executor::LowStack	&Executor::LowStack::operator = (Executor::LowStack const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char 	*Executor::LowStack::what() const throw()
{
	return "The stack is strictly inferior to 2";
}

/* Except Class */

Executor::OverflowCommand::OverflowCommand() throw()
{
	return ;
}

Executor::OverflowCommand::OverflowCommand(Executor::OverflowCommand const &obj) throw()
{
	*this = obj;
}

Executor::OverflowCommand::~OverflowCommand() throw()
{
	return ;
}

Executor::OverflowCommand	&Executor::OverflowCommand::operator = (Executor::OverflowCommand const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char 	*Executor::OverflowCommand::what() const throw()
{
	return "Will overflow";
}

/* Except Class */

Executor::UnderflowCommand::UnderflowCommand() throw()
{
	return ;
}

Executor::UnderflowCommand::UnderflowCommand(Executor::UnderflowCommand const &obj) throw()
{
	*this = obj;
}

Executor::UnderflowCommand::~UnderflowCommand() throw()
{
	return ;
}

Executor::UnderflowCommand	&Executor::UnderflowCommand::operator = (Executor::UnderflowCommand const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char 	*Executor::UnderflowCommand::what() const throw()
{
	return "Will underflow";
}

/* Except Class */

Executor::AfterExit::AfterExit() throw()
{
	return ;
}

Executor::AfterExit::AfterExit(Executor::AfterExit const &obj) throw()
{
	*this = obj;
}

Executor::AfterExit::~AfterExit() throw()
{
	return ;
}

Executor::AfterExit &Executor::AfterExit::operator = (Executor::AfterExit const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char *	Executor::AfterExit::what() const throw()
{
	return "Any command after exit";
}

/* Except Class */

Executor::NoDouble::NoDouble() throw()
{
	return ;
}

Executor::NoDouble::NoDouble(Executor::NoDouble const &obj) throw()
{
	*this = obj;
}

Executor::NoDouble::~NoDouble() throw()
{
	return ;
}

Executor::NoDouble &Executor::NoDouble::operator = (Executor::NoDouble const &obj) throw()
{
	static_cast<void>(obj);

	return *this;
}

const char *	Executor::NoDouble::what() const throw()
{
	return "One of values should be of the double type";
}