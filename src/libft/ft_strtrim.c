/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:22:23 by hlahrach          #+#    #+#             */
/*   Updated: 2021/11/07 15:08:09 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*p;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (malloc(1 * sizeof(char)));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	if (start >= ft_strlen(s))
		return (p);
	p = ft_strncpy(p, (char *)s + start, len);
	return (p);
}

int	ft_start(char const *s1, char const *set)
{
	int	i;
	int	len;
	int	len_l;

	len_l = 0;
	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (ft_strchr(set, s1[i]))
			len_l++;
		else
			break ;
		i++;
	}
	return (len_l);
}

int	ft_end(char const *s1, char const *set)
{
	int	len;
	int	len_b;

	len = ft_strlen(s1);
	len_b = len;
	while (len >= 0)
	{
		if (ft_strchr(set, s1[len]))
			len_b--;
		else
			break ;
		len--;
	}
	return (len_b);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	len_l;
	int	len_b;

	if (!s1 || !set)
		return (ft_strdup(""));
	if (!*s1)
		return (ft_strdup(""));
	len_l = ft_start(s1, set);
	len_b = ft_end(s1, set);
	if (len_l > len_b)
		return (ft_strdup(""));
	return (ft_substr2(s1, len_l, len_b - len_l + 1));
}
