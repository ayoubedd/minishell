/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:55:23 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/07 17:20:53 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	free_splits(char **list)
{
	size_t	i;

	i = 0;
	if (!list)
		return ;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static char	*get_key_value(t_exenv *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*search_for_cmd(char **dirs, char *cmd)
{
	char	*cmd_path;
	char	*tmp;
	size_t	i;

	i = 0;
	if (!dirs || !cmd)
		return (NULL);
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		if (!access(cmd_path, F_OK))
		{
			free(tmp);
			return (cmd_path);
		}
		free(tmp);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_exenv *env, char *cmd)
{
	char	**dirs;
	char	*path;
	char	*path_env;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	if (access(cmd, F_OK) != 0 && ft_strncmp(cmd, "./", 2) == 0)
		return (NULL);
	path_env = get_key_value(env, "PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	path = search_for_cmd(dirs, cmd);
	free_splits(dirs);
	return (path);
}
