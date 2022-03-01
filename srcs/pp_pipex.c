/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:28:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/01 13:11:42 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static int
	proc_child(t_cmd *cmd, char **env, pid_t *pid, int *fd)
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
		if (dup2(fd[0], STDIN) == -1)
			return (-1);
		if (dup2(fd[1], STDOUT) == -1)
			return (-1);
		close(fd[0]);
		close(fd[1]);
		//printf("excecute %s\n", cmd->cmd);
		ret = execve(cmd->cmd, cmd->arg, env);
		if (ret == -1)
		{
			printf("Error, execve\n");
			return (-1);
		}
	}
	return (0);
}

int
	pp_pipex(t_info *info, char **env)
{
	int		status;
	int		pipefd[2];
	int		fildes[2];
	pid_t	child;

	info->inf.fd = open(info->inf.path, O_RDONLY);
	info->ouf.fd = open(info->ouf.path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->inf.fd < 0 || info->ouf.fd < 0)
	{
		printf("Error, open infile/outfile\n");
		return (-42);
	}
	
	if (pipe(pipefd) == -1)
	{
		printf("Error, pipe function\n");
		return (-1);
	}

	close(pipefd[1]);

	fildes[0] = info->inf.fd;
	fildes[1] = pipefd[0];
	if (proc_child(&info->cmd1, env, &child, fildes))
		pp_brexit(info, -4);
	waitpid(child, &status, 0);


	fildes[0] = pipefd[0];
	fildes[1] = info->ouf.fd;
	if (proc_child(&info->cmd2, env, &child, fildes))
		pp_brexit(info, -5);
	waitpid(child, &status, 0);

	printf("I'm the parent!\n\n");

	printf("\nI waited my kids...\n");

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
 * │ wait_pid(child1_pid)
 * │ close(infile)
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
 * │wait_pid(child2_pid)
 * │close(outfile)
 * │end
 * ▼
 */
