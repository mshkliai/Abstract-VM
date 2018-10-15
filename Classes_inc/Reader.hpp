/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 14:21:03 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/16 14:21:03 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H

# include "../Inc/includes.h"

class	Reader
{

	public:
	
		Reader();
		Reader(Reader const &obj);
		~Reader();

		Reader						&operator = (Reader const &obj);

		std::vector<std::string>	getFileContent(std::string const &file_name);
		bool						getStatus();
		bool						getStream();

	private:

		bool		is_cin;
		bool		status_file;

		std::vector<std::string>	read_from_file(std::string const &file_name);
		std::vector<std::string>	read_from_cin();

		class BadFile : public std::exception
		{
			public:

				BadFile() throw();
				BadFile(BadFile const &obj) throw();
				~BadFile() throw();

				BadFile	&operator = (BadFile const &obj) throw();

				virtual const char * what() const throw(); 
			
		};
};

#endif
