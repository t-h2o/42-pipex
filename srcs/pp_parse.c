/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:29:39 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/23 15:26:06 by tgrivel          ###   ########.fr       */
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

static int
	pp_execve(t_info *info, char **search)
{
	char	*cmd;
	int		acc;
	char	**path;
	int		ret;

	path = info->path;
	ret = 0;
	while (*path)
	{
		cmd = ft_join_cmd(*path, *search);
		acc = access(cmd, X_OK);
		if (acc)
			free(cmd);
		else
			break ;
		path++;
	}
	if (!*path)
		ret = -1;
	else
	{
		free(*search);
		*search = cmd;
	}
	return (ret);
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
			break ;
		}
		env++;
	}
	if (!path)
		return ;
	info->path = pp_split(path, ':');
	return ;
}

void
	pp_parse(t_info *info, char **argv, char **env)
{
	get_info(info, env, "PATH=");
	info->inf = pp_strcpy(argv[1], 0, pp_strlen(argv[1]));
	info->ouf = pp_strcpy(argv[4], 0, pp_strlen(argv[4]));
	info->arg1 = pp_split(argv[2], ' ');
	info->cmd1 = info->arg1[0];
	info->arg1 = &(info->arg1[1]);
	info->arg2 = pp_split(argv[3], ' ');
	info->cmd2 = info->arg2[0];
	info->arg2 = &(info->arg2[1]);
	pp_execve(info, &info->cmd1);
	pp_execve(info, &info->cmd2);
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
