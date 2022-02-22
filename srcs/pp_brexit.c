/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brexit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:59:11 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/22 22:00:52 by tgrivel          ###   ########.fr       */
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

void
	free_info(t_info *info)
{
	free(info->inf);
	free(info->ouf);
	free(info->cmd1);
	free(info->cmd2);
	free_tab(info->path);
	free_tab(info->arg1);
	free_tab(info->arg2);
}
