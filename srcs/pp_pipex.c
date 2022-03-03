/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:28:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/03 14:11:28 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

int
	pp_pipex(t_info *info, char **env)
{
	int		status;
	int		pipefd[2];
	pid_t	child[2];

	info->inf.fd = open(info->inf.path, O_RDONLY);
	info->ouf.fd = open(info->ouf.path, O_CREAT | O_RDWR | O_TRUNC, 0644);

	if (pipe(pipefd) == -1)
		printf("Error, fail pipe\n");

	child[0] = fork();

	if (child[0] == -1)
		printf("Error, fork 1\n");

	if (!child[0])
	{
		if (dup2(info->inf.fd, STDIN) == -1)
			return (-1);
		if (dup2(pipefd[0], STDOUT) == -1)
			return (-1);
		close(info->inf.fd);
		close(info->ouf.fd);
		close(pipefd[1]);
		execve(info->cmd1.cmd, info->cmd1.arg, env);
		printf("Error, execve 1\n");
		return (-1);
	}

	child[1] = fork();

	if (child[1] == -1)
		printf("Error, fork 2\n");

	if (!child[1])
	{
		if (dup2(pipefd[1], STDIN) == -1)
			return (-1);
		//if (dup2(info->ouf.fd, STDOUT) == -1)
		//	return (-1);
		close(info->ouf.fd);
		close(pipefd[0]);
		execve(info->cmd2.cmd, info->cmd2.arg, env);
		printf("Error, execve 2\n");
		return (-1);
	}

	close(pipefd[0]);
	close(pipefd[1]);
	close(info->inf.fd);
	close(info->ouf.fd);

	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	return (0);
}
/*parent
 * │
 * │ open (infile)
 * │ pipe (fd[2])
 * │ close(fd[1])
 * │ fork()
 * │
 * │         child 1
 * ├───────────┐dup2(infile, STDIN)
 * │           │dup2(fd[0], STDOUT)
 * │           │close(infile)
 * │           │close(fd[0])
 * │           │execve(cmd, env)
 * │           ▼
 * │
 * │ open (outfile)
 * │ fork()
 * │
 * │         child 2
 * ├───────────┐dup2(fd[0], STDIN)
 * │           │dup2(outfile, STDOUT)
 * │           │close(fd[0])
 * │           │close(outfile)
 * │           │execve(cmd, env)
 * │           ▼
 * │
 * │close(infile)
 * │close(outfile)
 * │wait_pid(child1_pid)
 * │wait_pid(child2_pid)
 * │end
 * ▼
 */
