/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 10:39:25 by mshkliai          #+#    #+#             */
/*   Updated: 2018/09/22 19:37:06 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <iostream>
# include <deque>
# include <vector>
# include <fstream>
# include <cmath>
# include <ctype.h>
# include <string.h>
# include <limits>
# include <string>


# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define PURPLE "\033[1;35m"
# define END "\033[0m"

enum	eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

enum	eCommand
{
	push,
	pop,
	dump,
	pro_dump,
	assert,
	add,
	sub,
	mul,
	div,
	mod,
	power,
	print,
	print8,
	print16,
	print32,
	printfl,
	printd,
	exitt
};

typedef struct			s_command
{
	eCommand			name;
	eOperandType		type;
	std::string			value;
}						t_command;

#endif
