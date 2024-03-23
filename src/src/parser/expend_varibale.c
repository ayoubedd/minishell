/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_varibale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 10:50:07 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/09 17:19:05 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	return_char_exp(char s, char **tmp2)
{
	char	*tmp;
	char	*tmp3;

	tmp3 = *tmp2;
	tmp = convert_char_to_string(s);
	*tmp2 = ft_strjoin(tmp3, tmp);
	free (tmp3);
	free (tmp);
}

char	*expende_path_2(char *s, t_env *env, t_env **env_data, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		len;

	ft_malloc (NULL, &tmp2);
	while (s[i])
	{
		if (s[i] == '$')
		{
			tmp = expende_path2(s, env, i, &len);
			tmp3 = tmp2;
			tmp2 = ft_strjoin (tmp3, tmp);
			free (tmp3);
			free (tmp);
			i += len;
			env = (*env_data);
			continue ;
		}
		else
			return_char_exp (s[i], &tmp2);
		i++;
	}
	return (tmp2);
}

char	*parser_expend_variable(char *s, t_env **env_data)
{
	int		i;
	t_env	*env;
	char	*tmp2;

	i = 0;
	if (env_data == NULL || *env_data == NULL)
		return (NULL);
	env = (*env_data);
	tmp2 = expende_path_2(s, env, env_data, i);
	return (tmp2);
}
