/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 11:10:06 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/21 17:43:50 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/includes.h"

#include "../Classes_inc/IOperand.hpp"
#include "../Classes/Operand.hpp"
#include "../Classes_inc/Creator.hpp"
#include "../Classes_inc/Lexer.hpp"
#include "../Classes_inc/Parser.hpp"
#include "../Classes_inc/Executor.hpp"
#include "../Classes_inc/Reader.hpp"
#include "../Classes_inc/Avm.hpp"

static void			print_help(void)
{
	std::cout << GREEN << "push:" << END << " int8,16,32,float,double(value) -> adding new value in stack" << std::endl
		<< GREEN << "pop:" << END << " deleting top value in stack" << std::endl
		<< GREEN << "dump:" << END << " displaying all values in stack" << std::endl
		<< GREEN << "pro_dump:" << END << " displaying all detailed values in stack" << std::endl
		<< GREEN << "assert:" << END << " int8,16,32,float,double(value) -> checking top value in stack on true" << std::endl
		<< YELLOW << "add:" << END << " adds 2 top values -> delete them from stack and add result in top" << std::endl
		<< YELLOW << "sub:" << END << " substracts 2 top values -> delete them from stack and add result in top" << std::endl
		<< YELLOW << "mul:" << END << " multiplies 2 top values -> delete them from stack and add result in top" << std::endl
		<< YELLOW << "div:" << END << " divides 2 top values -> delete them from stack and add result in top" << std::endl
		<< YELLOW << "mod:" << END << " calc modulo of 2 top values -> delete them from stack and add result in top" << std::endl
		<< YELLOW << "power:" << END << "If one of values is of the double type, raises a top value to the power of second value"
		<< " -> delete them from stack and add result in top" << std::endl
		<< GREEN << "print:" << END << " print value in top of stack, if it is Int8 type" << std::endl
		<< RED << "exit:" << END << " terminate the execution of the current program, required attribute" << std::endl
		<< RED << ";" << END << " -> sign of comment" << std::endl;
}

int					main(int ac, char **av)
{
	if (ac > 2)
	{
		std::cerr << "Usage: ./avm" << std::endl
		<< "./avm file_name" << std::endl
		<< "./avm --help" << std::endl;
		return 0;
	}

	std::string	file_name;
	if (ac == 1) {
		file_name = "";
	}
	else if (static_cast<std::string>(av[1]) != "--help") {
		file_name = static_cast<std::string>(av[1]);
	}
	else
	{
		print_help();
		return 0;
	}
	
	Avm	avm(file_name);
	avm.execution();

	return 0;
}
