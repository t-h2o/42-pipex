/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:24:45 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/21 15:48:07 by tgrivel          ###   ########.fr       */
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

int
	main(void)
{
	test_split("I test my split function", ' ');
	test_split(" I test my split function", ' ');
	test_split("    I       test my split function", ' ');
	test_split("I test my split function   ", ' ');
	test_split(" a  ", ' ');
}
