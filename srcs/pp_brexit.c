/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_brexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:59:11 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/08 12:44:14 by tgrivel          ###   ########.fr       */
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
	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}
static void
	free_cmd(t_cmd *ptr)
{
	t_cmd	*tmp;
	while (ptr->next)
	{
		tmp = ptr->next;
		free(ptr->cmd);
		free_tab(ptr->arg);
		free(ptr);
		ptr = tmp;
	}

}

void
	pp_brexit(t_info *info, int exitValue)
{
	if (info)
	{
		free_set_null(&info->inf.path);
		free_set_null(&info->ouf.path);
		free_cmd(info->tcmd);
	}
	exit(exitValue);
}
