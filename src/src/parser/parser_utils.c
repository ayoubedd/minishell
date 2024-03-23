/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:17:53 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/23 20:18:20 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parser_get_string(char *s, char c)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_calloc (1, sizeof(char));
	tmp[0] = '\0';
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			tmp = ft_realloc(tmp, (ft_strlen(tmp) + 2));
			tmp[j++] = s[i];
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*parser_change_the_string(char *s, int token_type)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	i = 0;
	j = 0;
	tmp[0] = '\0';
	if (token_type == 7)
		tmp = parser_get_string (s, '"');
	else if (token_type == 8)
		tmp = parser_get_string (s, '\'');
	else
	{
		while (i < (int)ft_strlen (s))
		{
			tmp = ft_realloc (tmp, (ft_strlen(tmp) + 2));
			tmp[j++] = s[i];
			i++;
		}
		tmp[j] = '\0';
	}
	return (tmp);
}

int	convert_lexer(t_data **lexer)
{
	t_data	*tmp;
	char	*s;

	tmp = (*lexer);
	while (tmp)
	{
		s = parser_change_the_string(tmp->cmd, tmp->token_type);
		if (s == NULL)
			return (1);
		tmp->cmd = s;
		tmp = tmp->next;
	}
	return (0);
}

char	*convert_char_to_string(char c)
{
	char	*new;

	new = ft_calloc(2, sizeof(char));
	new[0] = c;
	new[1] = '\0';
	return (new);
}

int	calc(char *s)
{
	int	count;

	count = 0;
	while (s[count] != '=')
		count++;
	return (count);
}
