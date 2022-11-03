/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:15:46 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/03 16:15:48 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*res;

	if (!ptr)
		return (malloc(new_size));
	res = malloc(new_size);
	if (!res)
		return (NULL);
	if (size > new_size)
		size = new_size;
	ft_memmove(res, ptr, size);
	free(ptr);
	return (res);
}

char	*ft_strchr(const char *str, int chr)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == chr)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*c_dst;
	const char	*c_src;

	if (!dst || !src)
		return (NULL);
	c_dst = dst;
	c_src = src;
	i = -1;
	if (dst < src)
		while (++i < len)
			c_dst[i] = c_src[i];
	else
	{
		c_dst += len - 1;
		c_src += len - 1;
		while (++i < len)
			*c_dst-- = *c_src--;
	}
	return (dst);
}
