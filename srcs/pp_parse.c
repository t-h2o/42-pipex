/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:29:39 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/21 18:44:13 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"pipex.h"

static char
	*get_info(char **env, char *find)
{
	int	lenght;
	int	i;

	lenght = pp_strlen(find);
	while (*env)
	{
		i = 0;
		while ((*env)[i] == find[i] && i < lenght)
			i++;
		if (i == lenght)
			return (pp_strcpy(*env, i, pp_strlen(*env)));
		env++;
	}
	return (0);
}

void
	pp_parse(t_info *info, char **argv, char **env)
{
	char	*path;

	info->inf = argv[1];
	path = get_info(env, "PATH=");
	if (!path)
		return ;
	printf("all paths : %s\n", path);
	info->path = pp_split(path, ':');
	free(path);
}
/*		example of arguments:
 *
 *	./pipex infile cmd1 cmd2 outfile
 *	./pipex infile ``ls -l'' ``wc -l'' outfile
 */
