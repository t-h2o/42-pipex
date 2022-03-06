/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:55:03 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/06 12:09:47 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdarg.h>

static void
	my_strerror(char *str)
{
	while (*str)
	{
		write(2, str, 1);
		str++;
	}
}
/*	write the string in 
 *	the standard error output
 */

void	pp_errmsg(char *str, ...)
{
	va_list	arg;

	va_start(arg, str);
	while (*str)
	{
		if (*str == '%' && str[1] == 's')
		{
			my_strerror(va_arg(arg, char *));
			str += 2;
		}
		else
		{
			write(2, str, 1);
			str++;
		}
	}
	va_end(arg);
}
/*	As a pintf function,
 *	I set a variable argument lists
 */
