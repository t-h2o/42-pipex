/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_brexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:59:11 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/24 00:39:05 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static void
	free_tab(char **tab, int option)
{
	char	**save;

	save = tab;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	if (option)
		free(save);
}
/*	option 1
 *		free the tab
 *	option 0
 *		not free the tab
 */

void
	free_info(t_info *info)
{
	free(info->inf);
	free(info->ouf);
	free(info->cmd1.cmd);
	free(info->cmd2);
	free_tab(info->path, 1);
	free_tab(info->cmd1.arg, 0);
	free_tab(info->arg2, 0);
}
