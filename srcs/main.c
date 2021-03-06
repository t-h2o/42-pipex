/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:24:45 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/08 14:39:43 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static void
	init_info(t_info *info, char **argv, char **env)
{
	info->inf.path = 0;
	info->ouf.path = 0;
	info->tcmd = 0;
	info->envp = 0;
	info->tcmd = malloc(sizeof(t_cmd));
	if (info->tcmd == 0)
		pp_errmsg(info, -2, "pipex: malloc(): t_cmd");
	pp_parse(info, argv, env);
}
/*	Always set a structure
 */

int
	main(int argc, char **argv, char **env)
{
	t_info	info;

	if (argc < 5)
		pp_errmsg(0, 1, "pipex: usage: bad number of arguments");
	init_info(&info, argv, env);
	pp_pipex(&info, env);
	pp_brexit(&info, 0);
}
//	./pipex infile ``ls -l -a'' ``wc -l'' outfile
