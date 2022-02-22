/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <tgrivel@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:29:39 by tgrivel           #+#    #+#             */
/*   Updated: 2022/02/22 18:22:31 by tgrivel          ###   ########.fr       */
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

	path = get_info(env, "PATH=");
	if (!path)
		return ;
	info->path = pp_split(path, ':');
	info->inf = pp_strcpy(argv[1], 0, pp_strlen(argv[1]));
	info->ouf = pp_strcpy(argv[4], 0, pp_strlen(argv[4]));
	info->cmd1 = pp_strcpy(argv[2], 0, pp_strlen(argv[2]));
	info->cmd2 = pp_strcpy(argv[3], 0, pp_strlen(argv[3]));
	free(path);
}
/*		example of arguments:
 *
 *	./pipex infile cmd1 cmd2 outfile
 *	./pipex infile ``ls -l'' ``wc -l'' outfile
 */
