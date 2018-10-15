/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 14:55:55 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/15 14:55:55 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Avm.hpp"

Avm::Avm(std::string const & file_name) : errors(0)
{
	try {
		this->file_content = this->reader.getFileContent(file_name);
	}
	catch (std::exception &e) {
		std::cerr << RED << "Error: " << END << file_name
			<< ": " << e.what() << std::endl;
	}
}

Avm::Avm(Avm const &obj)
{
	*this = obj;
}

Avm::~Avm()
{
	 this->clearContainers();
}

Avm	&Avm::operator = (Avm const &)
{
	return *this;
}

/* Public Function */

void		Avm::execution()
{
	this->clearContainers();
	this->validation();

	if (this->errors > 0) {
		std::cout << "Total errors: " << this->errors << std::endl;
	}
	else if (this->commands.size() > 0)
	{
		for (size_t i = 0; i < this->commands.size(); i++)
		{
			try {
				this->executor.execute( *(this->commands[i]), &(this->avm_stack) );
			}
			catch (std::exception &e)
			{
				std::cerr << RED << "Execution error:" << END << std::endl
					<< e.what() << std::endl;
				break ;
			}
		}
	}
}

/* Private Functions */

void		Avm::validation()
{
	for (size_t i = 0; i < this->file_content.size(); i++)
	{
		try 
		{
			this->lexer.check_str(this->file_content[i]);
			t_command	*new_exec_command = this->parser.validate_command(this->lexer);
			
			if (new_exec_command != NULL) {
				this->commands.push_back(new_exec_command);
			}
			else if (new_exec_command == NULL && this->lexer.getCommand() != -1)
				this->errors++;
		}
		catch (std::exception & e)
		{
			std::cerr << RED << "Error" << END << " at line " << i + 1 << ": '"
			<< this->file_content[i] << "'" << std::endl
			<< e.what() << std::endl;
			this->errors++;
		}
	}

	if (this->reader.getStatus() == true) {
		this->handle_end_errors();
	}
}

void			Avm::handle_end_errors()
{
	try {
		this->lexer.check_end(this->reader.getStream(), this->parser.getExit(),
			this->file_content[this->file_content.size() - 1]);
	}
	catch (std::exception & e) {
		std::cerr << RED << "Error: " << END << e.what() << std::endl;
		this->errors++;
	}
}

void			Avm::clearContainers()
{
	for (size_t i = 0; i < this->commands.size(); i++) {
	 	delete this->commands[i];
	 }
	 this->commands.clear();

	 for (size_t i = 0; i < this->avm_stack.size(); i++) {
	 	delete this->avm_stack[i];
	 }
	 this->avm_stack.clear();
}