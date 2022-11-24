/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/24 15:12:38 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*expand_line(t_buff *b, char *s)
{
	char	*line;

	if (ft_strchr(b->buff + b->offset, '\n') != NULL)
		b->total_len += ft_strlen_c(b->buff + b->offset, '\n') + 1;
	else
		b->total_len += ft_strlen_c(b->buff + b->offset, '\0');
	line = (char *)malloc(sizeof(char) * (b->total_len + 1));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, s, b->total_len + 1);
	ft_strlcat(line, b->buff + b->offset, b->total_len + 1);
	free(s);
	if (ft_strchr(b->buff + b->offset, '\n') != NULL)
		b->offset += ft_strlen_c(b->buff + b->offset, '\n') + 1;
	else
		b->offset += ft_strlen_c(b->buff + b->offset, '\0');
	if (b->offset == b->nbytes && b->nbytes < BUFFER_SIZE)
		b->offset = -1;
	if (b->offset == BUFFER_SIZE)
		b->offset = 0;
	return (line);
}

int	read_file(int fd, t_buff *b)
{
	b->nbytes = read(fd, b->buff, BUFFER_SIZE);
	b->buff[b->nbytes] = '\0';
	b->offset = 0;
	return (b->nbytes);
}

static char	*make_next_line(int fd, t_buff *b)
{
	char	*line;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	while (b->offset != -1)
	{
		if (b->offset == 0)
		{
			read_file(fd, b);
			if (ft_strlen_c(line, '\0') > 0 && b->nbytes == 0)
				return (line);
			if (b->nbytes <= 0)
			{
				b->offset = 0;
				free(line);
				return (NULL);
			}
		}
		line = expand_line(b, line);
		if (ft_strchr(line, '\n') != NULL || b->offset == -1)
			return (line);
	}
	b->offset = 0;
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_buff	buffer;
	char			*new_line;

	buffer.total_len = 0;
	new_line = make_next_line(fd, &buffer);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
