/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:41:51 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/22 22:07:20 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//	Include

# include	<stdio.h>
# include	<stdlib.h>

//	Structur

typedef struct s_info {
	char	*inf;
	char	*ouf;
	char	*cmd1;
	char	*cmd2;
	char	**arg1;
	char	**arg2;
	char	**path;
}	t_info;
/*	inf ~ input file
 *	ouf ~ output file
 *	cmd ~ commande
 *	arg ~ arguments of the commande
 *	path
 *		all path of binaries
 * 
 */

//	pp_brexit.c


void	free_info(t_info *info);

//	pp_parse.c

void	pp_parse(t_info *info, char **argv, char **env);

//	pp_split.c

char	**pp_split(char *str, char c);
char	*pp_strcpy(char *str, int s, int e);
int		pp_strlen(char *str);

#endif /* PIPEX_H */
