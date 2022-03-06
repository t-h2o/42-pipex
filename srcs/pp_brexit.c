/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_brexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:59:11 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/06 14:18:52 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static void
	free_set_null(char **str)
{
	free(*str);
	*str = 0;
}

static void
	free_tab(char ***tab)
{
	int		i;

	i = 0;
	if (*tab == 0)
		return ;
	while (tab[0][i])
	{
		free_set_null(&(tab[0][i]));
		i++;
	}
	free(*tab);
	*tab = 0;
}

void
	pp_brexit(t_info *info, int exitValue)
{
	if (info)
	{
		free_tab(&info->cmd1.arg);
		free_tab(&info->cmd2.arg);
		free_set_null(&info->cmd1.cmd);
		free_set_null(&info->cmd1.cmd);
		free_set_null(&info->inf.path);
		free_set_null(&info->ouf.path);
	}
	exit(exitValue);
}
