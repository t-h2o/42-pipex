/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_brexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:59:11 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/25 14:12:31 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static void
	free_tab(char **tab)
{
	char	**save;

	save = tab;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(save);
}
/*	free each line and the tab
 */

void
	pp_brexit(t_info *info, int exitValue)
{
	free(info->inf);
	free(info->ouf);
	free(info->cmd1.cmd);
	free_tab(info->cmd1.arg);
	free(info->cmd2.cmd);
	free_tab(info->cmd2.arg);
	free_tab(info->path);
	exit(exitValue);
}
