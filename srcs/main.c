/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:24:45 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/25 14:12:11 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static void
	display_tab(char **tab, char *s)
{
	while (*tab)
	{
		printf("%s\t%s\n", s, *tab);
		tab++;
	}
}

static void
	test_parse(t_info *info)
{
	printf("infile\t: %s\n", info->inf);
	printf("cmd 1\t: %s\n", info->cmd1.cmd);
	display_tab(info->cmd1.arg, "\targ1");
	printf("cmd 2\t: %s\n", info->cmd2.cmd);
	display_tab(info->cmd2.arg, "\targ2");
	printf("outfile\t: %s\n", info->ouf);
}
//	./pipex infile ``ls -l'' ``wc -l'' outfile

static int
	init_info(t_info *info, char **argv, char **env)
{
	info->inf = 0;
	info->ouf = 0;
	info->cmd1.cmd = 0;
	info->cmd1.arg = 0;
	info->cmd2.cmd = 0;
	info->cmd2.arg = 0;
	info->path = 0;
	return (pp_parse(info, argv, env));
}

int
	main(int argc, char **argv, char **env)
{
	t_info	info;

	if (argc != 5)
		printf("Error, bad number of arguments\n");
	if (argc != 5)
		return (2);

	if (init_info(&info, argv, env))
	{
		pp_brexit(&info, 12);
		return (3);
	}
	
	test_parse(&info);	// display information

	pp_pipex(&info, env);

	pp_brexit(&info, 23);

	return (0);
}
//	./pipex infile ``ls -l -a'' ``wc -l'' outfile
