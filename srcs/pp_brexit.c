/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_brexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:59:11 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/06 17:32:34 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static void
	free_set_null(char **str)
{
	free(*str);
	*str = 0;
}

void
	pp_brexit(t_info *info, int exitValue)
{
	if (info)
	{
		free_set_null(&info->inf.path);
		free_set_null(&info->ouf.path);
	}
	exit(exitValue);
}
