/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:28:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/24 16:17:37 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int
	pp_pipex(t_info *info)
{
	(void)info;
	int		status;
	int		pipefd[2];
	pid_t	child[2];

	if (pipe(pipefd) == -1)
	{
		printf("Error, pipe function\n");
		return (-1);
	}

	child[0] = fork();
	if (child[0] == -1)
	{
		printf("Error, 1st fork\n");
		return (-1);
	}
	if (child[0] == 0) // child
	{
		printf("I'am the 1st child\n");
		exit(0);
	}
	

	child[1] = fork();
	if (child[1] == -1)
	{
		printf("Error, 1st fork\n");
		return (-1);
	}
	if (child[1] == 0) // child
	{
		printf("I'am the 2nd child\n");
		exit(0);
	}

	printf("I'm the parent!\n");

	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);

	printf("I waited my kids...\n");

	return (0);
}
