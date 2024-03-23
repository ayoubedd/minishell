/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:12:47 by hlahrach          #+#    #+#             */
/*   Updated: 2021/11/13 21:05:50 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "stdio.h"

char	*ft_substr3(const char *s, int start, size_t len)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!s || !p)
		return (NULL);
	while (i < len && s[i])
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	word_count(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
			continue ;
		}
		i++;
	}
	return (count);
}

int	word_len(const char *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len++;
			i++;
		}
		else
			return (len);
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	p = (char **)malloc (sizeof(char *) * (word_count(s, c) + 1));
	if (!p)
		return (NULL);
	while (i < (word_count(s, c)))
	{
		while (s[j] && s[j] == c)
			j++;
		len = word_len(s + j, c);
		p[i] = ft_substr3(s, j, len);
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	p[word_count(s, c)] = NULL;
	return (p);
}
