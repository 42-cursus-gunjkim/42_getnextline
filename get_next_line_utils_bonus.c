/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:56:58 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/24 12:52:13 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_c(const char *s, const char c)
{
	size_t	length;

	length = 0;
	while (s[length] != c)
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len_with_null;
	size_t	i;

	len_with_null = ft_strlen_c(s, '\0') + 1;
	i = 0;
	c = (char)c;
	while (i < len_with_null)
	{
		if (s[i] == c)
			return ((char *)(&s[i]));
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen_c(src, '\0'));
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen_c(src, '\0'));
}

char	*ft_strdup(const char *s1)
{
	size_t	len_with_null;
	size_t	index;
	char	*copy;

	index = 0;
	len_with_null = ft_strlen_c(s1, '\0') + 1;
	copy = (char *)malloc(sizeof(char) * len_with_null);
	if (copy == NULL)
		return (NULL);
	while (s1[index])
	{
		copy[index] = s1[index];
		index++;
	}
	copy[index] = '\0';
	return (copy);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen_c(src, '\0'));
	i = 0;
	dst_len = ft_strlen_c(dst, '\0');
	src_len = ft_strlen_c(src, '\0');
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	while (dst_len + i + 1 < dstsize && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
