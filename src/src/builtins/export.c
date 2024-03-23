/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddaoud <aeddaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:33:31 by aeddaoud          #+#    #+#             */
/*   Updated: 2022/09/12 23:09:28 by aeddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/execution.h"
#include "../../includes/builtins.h"

static void	print(t_exenv *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
		{
			printf("=\"%s\"", env->value);
		}
		printf("\n");
		env = env->next;
	}
}

t_bool	valid_key_check(char *key)
{
	size_t	i;

	i = 1;
	if (!(key[0] >= 'a' && key[0] <= 'z')
		&& !(key[0] >= 'A' && key[0] <= 'Z')
		&& key[0] != '_')
		return (TRUE);
	while (key[i])
	{
		if (!(key[i] >= 'a' && key[i] <= 'z')
			&& !(key[i] >= 'A' && key[i] <= 'Z')
			&& !(key[i] >= '0' && key[i] <= '9')
			&& key[i] != '_')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	export_variable(t_exenv **env, t_exenv *tmp, char *arg)
{
	char	*value;

	if (tmp)
	{
		value = extract_value(arg);
		if (!value)
			return ;
		free(tmp->value);
		tmp->value = value;
		return ;
	}
	tmp = malloc(sizeof(t_exenv));
	if (!tmp)
		return ;
	tmp->key = extract_key(arg);
	tmp->value = extract_value(arg);
	tmp->next = NULL;
	exenv_add_back(env, tmp);
}

static t_bool	export_var(t_exenv **env, char **args)
{
	size_t	i;
	t_exenv	*tmp;
	char	*search_key;
	t_bool	error;

	i = 0;
	error = FALSE;
	while (args[i++])
	{
		search_key = extract_key(args[i - 1]);
		if (valid_key_check(search_key))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(search_key, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			free(search_key);
			error = TRUE;
			continue ;
		}
		tmp = find_item(*env, search_key);
		export_variable(env, tmp, args[i - 1]);
		free(search_key);
	}
	return (error);
}

void	export_blt(t_exec *exec, t_cmd *cmd)
{
	t_bool	error;

	error = FALSE;
	if (!cmd->args[1])
		print(exec->env);
	else
		error = export_var(&exec->env, &cmd->args[1]);
	if (error)
		g_exit_code = EXIT_FAILURE;
	else
		g_exit_code = EXIT_SUCCESS;
}
