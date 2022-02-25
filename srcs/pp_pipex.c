/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:28:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/25 13:59:23 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static int
	proc_child(t_cmd *cmd, char **env, pid_t *pid)
{
	int	ret;

	*pid = fork();
	if (*pid == -1)
	{
		printf("Error, 1st fork\n");
		return (-1);
	}
	if (*pid == 0)
	{
		printf("excecute %s\n", cmd->cmd);
		ret = execve(cmd->cmd, cmd->arg, env);
		if (ret == -1)
			printf("Error, execve\n");
	}
	return (0);
}

int
	pp_pipex(t_info *info, char **env)
{
	int		status;
	int		pipefd[2];
	pid_t	child[2];

	if (pipe(pipefd) == -1)
	{
		printf("Error, pipe function\n");
		return (-1);
	}

	if (proc_child(&info->cmd1, env, &child[0]))
		pp_brexit(info, -4);
	waitpid(child[0], &status, 0);

	if (proc_child(&info->cmd2, env, &child[1]))
		pp_brexit(info, -5);
	waitpid(child[1], &status, 0);

	printf("I'm the parent!\n\n");

	printf("\nI waited my kids...\n");

	return (0);
}
/* Parent
 * │
 * │Fork()
 * │         Child 0
 * ├─────────┐
 * │         │
 * │Fork()   ▼
 * │         Child 1
 * ├─────────┐
 * │         │
 * ▼         ▼
 */
