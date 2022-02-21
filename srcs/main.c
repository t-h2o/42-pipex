/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:24:45 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/21 18:41:02 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

void	test_split(char *str, char c)
{
	printf("\n\tDEBUT TEST\n\n");
	
	char	**tab;
	char	**save;
	int		i;

	i = -1;
	while (++i < 30)
		printf("%d",i%10);

	printf("\n%s\n", str);
	tab = pp_split(str, c);
	save = tab;
	while (*tab)
	{
		printf("m ");
		printf("%s\n", *tab);
		free(*tab);
		*tab = 0;
		tab++;
	}
	printf("\n\tFIN  TEST\n");
	free(save);
}

void	test_parse(t_info *info)
{
	printf("infile\t: %s\n", info->inf);
	//printf("outfile\t: %s\n", info.ouf);
	//printf("path\t: %s\n", info.path[0]);
}

int
	main(int argc, char **argv, char **env)
{
	t_info	info;

	if (argc < 2)
		return (0);
	pp_parse(&info, argv, env);
	test_parse(&info);
}
