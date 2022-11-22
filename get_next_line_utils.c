/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:56:58 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/22 17:32:52 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len_with_null;
	size_t	i;

	len_with_null = ft_strlen(s) + 1;
	i = 0;
	c = (char)c;
	while (i < len_with_null)
	{
		if (*s == c)
			return (s);
		s++;
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
