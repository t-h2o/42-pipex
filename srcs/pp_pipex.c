/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:28:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/04 11:51:50 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

# define	PIPE_WRITE	1
# define	PIPE_READ	0

int
	pp_pipex(t_info *info, char **env)
{
	int		status;
	int		fd[2];
	pid_t	child;

	info->inf.fd = open(info->inf.path, O_RDONLY);
	if (info->inf.fd < 0)
		printf("Error, infile open\n");

	info->ouf.fd = open(info->ouf.path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->ouf.fd < 0)
		printf("Error, outfile open\n");

	if (pipe(fd) == -1)
		printf("Error, pipe\n");

	child = fork();

	if (child == -1)
		printf("Error, fork\n");

	if (child == 0)	// child
	{
		dup2(info->inf.fd, STDIN);
		dup2(fd[PIPE_WRITE], STDOUT);
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
		execve(info->cmd1.cmd, info->cmd1.arg, env);
		printf("Error cmd 1\n");
	}
	else
	{
		dup2(fd[PIPE_READ], STDIN);
		dup2(info->ouf.fd, STDOUT);
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
		waitpid(child, &status, 0);
		execve(info->cmd2.cmd, info->cmd2.arg, env);
		printf("Error cmd 2\n");
	}

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
