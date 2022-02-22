/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:37:16 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/22 22:09:12 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int	pp_strlen(char *str)
{
	int	r;

	r = 0;
	while (str[r])
		r++;
	return (r);
}
//	return the lenght of the string

static int
	line_counter(char *str, char c)
{
	int	r;

	r = 1;
	if (*str == c)
		r = 0;
	while (*str)
	{
		if (*str == c)
		{
			r++;
			while (str[1] == c)
				str++;
		}
		str++;
	}
	if (*(--str) == c)
		r--;
	return (r);
}
// count the number of separation.

char
	*pp_strcpy(char *str, int s, int e)
{
	int		lenght;
	char	*r;

	lenght = e - s + 1;
	r = (char *)malloc(lenght + 1);
	if (!r)
		return (0);
	r[lenght] = 0;
	while (lenght--)
		r[lenght] = str[s + lenght];
	return (r);
}
/*	start(s), end(e)
 *	copy from start to end
 *
 * 	example :
 *	("I try split", 0, 0)
 *	return("I")
 *
 *	("I try split", 2, 4)
 *	end		= 4
 *	start	= 2
 *	return("try")
 */

char
	**pp_split(char *str, char c)
{
	char	**r;
	int		line;
	int		start;
	int		end;
	int		i;

	line = line_counter(str, c);
	r = (char **)malloc(sizeof(char *) * line + 1);
	if (!r)
		return (0);
	r[line] = 0;
	end = 0;
	i = 0;
	while (line--)
	{
		while (str[end] == c)
			end ++;
		start = end;
		while (str[end] != 0 && str[end] != c)
			end ++;
		r[i] = pp_strcpy(str, start, end - 1);
		if (!r[i++])
			return (0);
	}
	return (r);
}
/*	function split:
 *	("split_function_by_theo", '_');
 *	{"split", "function", "by", "theo"}
 */
