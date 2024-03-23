/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_variable1_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:11:07 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 16:01:33 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expende_path2(char *s, t_env *env, int i, int *len)
{
	int		k;
	char	*tmp;

	k = 0;
	k = return_pointer(s, '$', i);
	if (k == 0)
		k = ft_strlen(s);
	tmp = ft_substr(s, i, k - i);
	*len = ft_strlen(tmp);
	while (env)
	{
		if (ft_strncmp(env->env, tmp + 1, calc(env->env)) == 0
			&& ft_strncmp(env->env, tmp + 1, ft_strlen(tmp + 1)) == 0)
			break ;
		env = env->next;
	}
	k = ft_strlen (tmp);
	free (tmp);
	if (env == NULL)
		return (ft_strdup (""));
	return (ft_strdup(env->env + k));
}

void	return_char_exp2(char s, char **tmp2, int *check)
{
	char	*tmp;
	char	*tmp3;

	if (s == '$')
		*check = 0;
	tmp3 = *tmp2;
	tmp = convert_char_to_string(s);
	*tmp2 = ft_strjoin(tmp3, tmp);
	free (tmp3);
	free (tmp);
}

void	copy_exit_code(char **new, int *i)
{
	char	*tmp;
	char	*tmp3;

	tmp3 = *new;
	tmp = ft_itoa(g_exit_code);
	*new = ft_strjoin(tmp3, tmp);
	free (tmp);
	free (tmp3);
	*i = *i + 1;
}

char	*expende_path(char *s, t_env **env_data, char **new, int i)
{
	int		check;
	int		n;

	ft_malloc (NULL, new);
	n = 0;
	check = 0;
	while (s[i])
	{
		is_singleqoutes (s[i], &n, check);
		if ((s[i] == '<' && s[i + 1] == '<'))
			check = 1;
		if (s[i] == '$' && s[i + 1] != '?' && n == 0 && check == 0)
			copy_path (s, env_data, new, &i);
		else if (s[i] == '$' && s[i + 1] == '?')
			copy_exit_code (new, &i);
		else
			return_char_exp2(s[i], new, &check);
		i++;
	}
	is_singleqoutes ('\0', 0, 2);
	return (NULL);
}

char	*parser_new_string(char *s, t_env **env_data, int token_type)
{
	int		i;
	char	*tmp2;

	i = 0;
	if (token_type == 8 || token_type == 3)
		return (ft_strdup (s));
	expende_path (s, env_data, &tmp2, i);
	return (tmp2);
}
