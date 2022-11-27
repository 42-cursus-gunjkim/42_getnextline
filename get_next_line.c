/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/27 15:10:12 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*expand_line(t_buff *b, char *s)
{
	char	*line;
	size_t	added;

	if (ft_strchr(b->buff, '\n') != NULL)
		b->total_len += ft_strlen_c(b->buff, '\n') + 1;
	else
		b->total_len += ft_strlen_c(b->buff, '\0');
	line = (char *)malloc(sizeof(char) * (b->total_len + 1));
	if (line == NULL)
	{
		free(s);
		return (NULL);
	}
	ft_strlcpy(line, s, b->total_len + 1);
	ft_strlcat(line, b->buff, b->total_len + 1);
	added = ft_strlen_c(line, '\0') - ft_strlen_c(s, '\0');
	ft_strlcpy(b->buff, b->buff + added, BUFFER_SIZE + 1);
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
		if (ft_strlen_c(b->buff, '\0') == 0)
		{
			b->nbytes = read(fd, b->buff, BUFFER_SIZE);
			b->buff[b->nbytes] = '\0';
			if (ft_strlen_c(line, '\0') > 0 && b->nbytes == 0)
				return (line);
			if (b->nbytes <= 0)
			{
				b->buff[0] = '\0';
				free(line);
				return (NULL);
			}
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
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
