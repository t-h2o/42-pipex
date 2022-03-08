/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tggrivel@student.42lausanne.ch>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:28:05 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/08 13:57:24 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

#define PIPE_WRITE 1
#define PIPE_READ 0

static void
	openfiles(t_info *info, int *fd)
{
	info->inf.fd = open(info->inf.path, O_RDONLY);
	if (info->inf.fd < 0)
		pp_errmsg(info, 1, "pipex: Error: cannot open infile");
	info->ouf.fd = open(info->ouf.path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->ouf.fd < 0)
		pp_errmsg(info, 1, "pipex: Error: cannot open outfile");
	if (pipe(fd) == -1)
		pp_errmsg(info, 1, "pipex: Error: pipe");
}

static void
	subprocess(int inf, int ouf, int *fd)
{
	dup2(inf, STDIN);
	dup2(ouf, STDOUT);
	close(fd[PIPE_READ]);
	close(fd[PIPE_WRITE]);
}

void
	pp_pipex(t_info *info, char **env)
{
	int		fd[2];
	pid_t	child;
	t_cmd	*ptr;

	openfiles(info, fd);
	ptr = info->tcmd;
	child = fork();
	if (child == -1)
		pp_errmsg(info, 1, "pipex: Error: fork");
	if (child == 0)
	{
		subprocess(info->inf.fd, fd[PIPE_WRITE], fd);
		execve(ptr->cmd, ptr->arg, env);
		pp_errmsg(info, 1, "pipex: Error: execve");
	}
	ptr = ptr->next;
	subprocess(fd[PIPE_READ], info->ouf.fd, fd);
	execve(ptr->cmd, ptr->arg, env);
	pp_errmsg(info, 1, "pipex: Error: execve");
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
