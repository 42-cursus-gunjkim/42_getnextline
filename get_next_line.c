/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/28 00:32:49 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*expand_line(t_buff *b, char *s)
{
	char	*line;
	size_t	added;

	if (ft_strchr(b->buff + b->offset, '\n') != NULL)
		b->total_len += ft_strlen_c(b->buff + b->offset, '\n') + 1;
	else
		b->total_len += ft_strlen_c(b->buff + b->offset, '\0');
	line = (char *)malloc(sizeof(char) * (b->total_len + 1));
	if (line == NULL)
	{
		free(s);
		return (NULL);
	}
	ft_strlcpy(line, s, b->total_len + 1);
	ft_strlcat(line, b->buff + b->offset, b->total_len + 1);
	added = b->total_len - ft_strlen_c(s, '\0');
	b->offset += added;
	if (b->offset == (unsigned long)b->nbytes)
		b->offset = 0;
	free(s);
	return (line);
}

static char	*make_next_line(int fd, t_buff *b)
{
	char	*line;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	while (ft_strchr(line, '\n') == NULL)
	{
		if (b->offset == 0)
		{
			b->nbytes = read(fd, b->buff, BUFFER_SIZE);
			if (ft_strlen_c(line, '\0') > 0 && b->nbytes == 0)
				return (line);
			if (b->nbytes <= 0)
			{
				b->offset = 0;
				free(line);
				return (NULL);
			}
			b->buff[b->nbytes] = '\0';
		}
		line = expand_line(b, line);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buff	buffer[OPEN_MAX];
	char			*new_line;

	if (fd < 0)
		return (NULL);
	buffer[fd].total_len = 0;
	new_line = make_next_line(fd, &buffer[fd]);
	return (new_line);
}
