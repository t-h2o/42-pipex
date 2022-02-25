/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:41:51 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/24 17:37:08 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//	Include

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>

//	Structur

typedef struct s_cmd {
	char	*cmd;
	char	**arg;
}	t_cmd;

typedef struct s_info {
	char	*inf;
	char	*ouf;
	t_cmd	cmd1;
	t_cmd	cmd2;
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

//	pp_pipex.c

int		pp_pipex(t_info *info, char **env);

#endif /* PIPEX_H */
