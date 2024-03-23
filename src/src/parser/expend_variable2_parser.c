/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_variable2_parser.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <hlahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:04:51 by hlahrach          #+#    #+#             */
/*   Updated: 2022/09/12 15:58:14 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_singleqoutes(char c, int *n,	int check)
{
	static int	m;
	static int	i;

	if (check == 2)
	{
		m = 0;
		i = 0;
		return ;
	}
	if (i == 2)
	{
		*n = 0;
		i = 0;
	}
	if (m == 2)
		m = 0;
	if (c == '"' && i == 0)
		m++;
	if (c == '\'')
		i++;
	if (i == 1 && m == 0)
		*n = 1;
}

int	return_pointer(char *s, char c, int l)
{
	int	i;

	i = l + 1;
	(void)c;
	while (s[i])
	{
		if (s[i] == '$' || s[i] == ' ' || s[i] == '"'
			|| s[i] == '\'' || s[i] == '-' || s[i] == '=')
		{
			return (i);
		}
		i++;
	}
	return (0);
}

void	copy_path(char *s, t_env **env_data, char **new, int *i)
{
	int		len;
	char	*tmp;
	char	*tmp3;

	tmp = expende_path2(s, *env_data, *i, &len);
	tmp3 = (*new);
	(*new) = ft_strjoin (tmp3, tmp);
	free (tmp3);
	free (tmp);
	*i += len - 1;
}
