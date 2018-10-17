/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:20:58 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/16 14:20:59 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Reader.hpp"

Reader::Reader()
{
	this->status_file = true;
	this->is_cin = false;
}

Reader::Reader(Reader const &obj)
{
	*this = obj;
}

Reader::~Reader()
{
	return ;
}

Reader							&Reader::operator = (Reader const &obj)
{
	this->is_cin = obj.is_cin;
	this->status_file = obj.status_file;

	return *this;
}

/* Getter */

std::vector<std::string>		Reader::getFileContent(std::string const &file_name)
{
	if (file_name.length() == 0)
	{
		this->is_cin = true;
		return read_from_cin();
	}
	
	return read_from_file(file_name);
}

bool							Reader::getStatus()
{
	return this->status_file;
}

bool							Reader::getStream()
{
	return this->is_cin;
}

/* Functions */

std::vector<std::string>		Reader::read_from_file(std::string const &file_name)
{
	std::ifstream				fd(file_name);

	if (fd.is_open() == false) 
	{
		this->status_file = false;
		throw std::invalid_argument("No such file");
	}
	else
	{
		char						buff[1000000];
		std::vector<std::string>	file_content;
	
		while (fd.getline(buff, 1000000)) {
			file_content.push_back(static_cast<std::string>(buff));
		}
		fd.close();

		return file_content;
	}
}

std::vector<std::string>		Reader::read_from_cin()
{
	std::string					one_str;
	std::vector<std::string>	cin_content;

	while (std::cin >> one_str)
	{
		if ( cin_content.size() > 0 && one_str.find('(') != std::string::npos &&
		( cin_content[cin_content.size() - 1] == "push" ||
		cin_content[cin_content.size() - 1] == "assert" ))
		{
			cin_content[cin_content.size() - 1] += " " + one_str;
		}
		else
		{
			cin_content.push_back(static_cast<std::string>(one_str));
			if (one_str == ";;") {
				break ;
			}
		}
	}

	return cin_content;
}