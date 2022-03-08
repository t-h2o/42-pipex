/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:29:39 by tgrivel           #+#    #+#             */
/*   Updated: 2022/03/08 14:02:55 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static char
	*ft_join_cmd(char *s1, char *s2)
{
	char	*r;
	int		len;
	int		i;

	len = 1;
	i = -1;
	while (s1[++i])
		len++;
	i = -1;
	while (s2[++i])
		len++;
	r = (char *)malloc(len + 1);
	if (!r)
		return (0);
	r[len] = 0;
	i = 0;
	len = 0;
	while (s1[i])
		r[len++] = s1[i++];
	r[len++] = '/';
	i = 0;
	while (s2[i])
		r[len++] = s2[i++];
	return (r);
}

static void
	find_path_cmd(t_info *info, char **search)
{
	char	*cmd;
	char	**path;

	path = info->envp;
	while (*path)
	{
		cmd = ft_join_cmd(*path, *search);
		if (!cmd)
			pp_errmsg(info, 89, "pipex: Error: join return 0");
		if (access(cmd, X_OK))
			free(cmd);
		else
			break ;
		path++;
	}
	if (!*path)
		pp_errmsg(info, 89, "pipex: %s: command not found", *search);
	free(*search);
	*search = cmd;
}

static void
	get_info(t_info *info, char **env, char *find)
{
	char	*path;
	int		lenght;
	int		i;

	path = 0;
	lenght = pp_strlen(find);
	while (*env)
	{
		i = 0;
		while ((*env)[i] == find[i] && i < lenght)
			i++;
		if (i == lenght)
		{
			path = pp_strcpy(*env, i, pp_strlen(*env));
			if (!path)
				pp_errmsg(info, -2, "pipex: Error: Cannot find path in env");
			break ;
		}
		env++;
	}
	info->envp = pp_split(path, ':');
	return ;
}
/*	get all path of binary
 *	put the info in tab**
 */

static void
	parse_cmd(t_info *info, char **argv)
{
	t_cmd	*ptr;
	int		i;

	info->tcmd = malloc(sizeof(t_cmd));
	ptr = info->tcmd;
	i = 0;
	while (1)
	{
		ptr->arg = pp_split(argv[2 + i], ' ');
		ptr->cmd
			= pp_strcpy(ptr->arg[0], 0, pp_strlen(ptr->arg[0]));
		ptr->next = 0;
		find_path_cmd(info, &ptr->cmd);
		if (argv[4 + i])
		{
			ptr->next = malloc(sizeof(t_cmd));
			if (ptr->next == 0)
				pp_errmsg(info, -2, "pipex: Error: malloc t_cmd");
			ptr = ptr->next;
		}
		else
			break ;
		i++;
	}
}
/*
 * *tcmd───►cmd
 *          arg
 *          *next───►cmd
 *                   arg
 *                   *next───► 0
 */

void
	pp_parse(t_info *info, char **argv, char **env)
{
	get_info(info, env, "PATH=");
	info->inf.path = pp_strcpy(argv[1], 0, pp_strlen(argv[1]));
	info->ouf.path = pp_strcpy(argv[4], 0, pp_strlen(argv[4]));
	parse_cmd(info, argv);
}
/*		example of arguments:
 *
 *	./pipex infile cmd1 cmd2 outfile
 *	./pipex infile ``ls -l'' ``wc -l'' outfile
 */
/*	command
 *
 *	cmd1 = "cmd arg1 arg2"
 *	arg1 = "cmd" "arg1" "arg2"
 */
