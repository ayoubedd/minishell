/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 11:14:10 by hlahrach          #+#    #+#             */
/*   Updated: 2022/07/22 11:30:52 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

void	*ft_realloc(void *ptr, size_t len)
{
	void	*new;

	new = malloc(len);
	memset(new, 0, len);
	if (new)
		ft_memcpy(new, ptr, len);
	return (new);
}

int	ft_error(char *s, int n)
{
	write(2, s, ft_strlen(s));
	return (n);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (p1[i] != '\0' || p2[i] != '\0')
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

int	check_case(t_lexer *lexer)
{
	if ((lexer->c == '<' || lexer->c == '>' || lexer->c == '|'
			|| lexer->c == ' ' || lexer->c == '\0'))
		return (1);
	return (0);
}

int	check_case2(t_lexer *lexer)
{
	if ((lexer->c == '"' || lexer->c == '\'')
		&& (lexer->cmd[lexer->index + 1] == '<'
			|| lexer->cmd[lexer->index + 1] == '>'
			|| lexer->cmd[lexer->index + 1] == '|'))
		return (1);
	return (0);
}
