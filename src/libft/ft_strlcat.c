/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlahrach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:21:16 by hlahrach          #+#    #+#             */
/*   Updated: 2021/11/11 18:40:57 by hlahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	if (dstsize <= 0)
		return (dstsize + ft_strlen(src));
	k = 0;
	i = ft_strlen(src);
	j = ft_strlen(dst);
	len = j;
	if (dstsize < j + 1)
		return (dstsize + i);
	else
	{
		while (src[k] && j < dstsize - 1)
		{
			dst[j] = src[k];
			k++;
			j++;
		}
	}
	dst[j] = '\0';
	return (i + len);
}
