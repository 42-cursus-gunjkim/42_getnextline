/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/23 20:39:17 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*expand_line(t_buff *b, char *s)
{
	char	*line;
	size_t	add_size;

	line = (char *)malloc(sizeof(char) * (b->total_len + 1));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, s, b->total_len);
	ft_strlcat(line, b->buff, b->total_len + 1);
	free(s);
	return (line);
}

int	read_file(int fd, t_buff *b)
{
	int	nbytes;

	nbytes = read(fd, b->buff, BUFFER_SIZE);
	b->buff[nbytes] = '\0';
	b->offset = 0;
	return (nbytes);
}

static char	*make_next_line(int fd, t_buff *b)
{
	char	*line_tmp;
	char	*line;
	int		nbytes;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	if (b->offset == 0 || b->offset >= BUFFER_SIZE)
	{
		nbytes = read_file(fd, b);
		if (nbytes == -1)
			return (NULL);
		b->offset = 0;
	}
	while (ft_strchr(b->buff + b->offset, '\n') == NULL)
	{
		b->total_len += ft_strlen_c(b->buff + b->offset, '\0');
		line = expand_line(b, line);
		nbytes = read_file(fd, b);
		if (nbytes == -1)
			return (NULL);
		if (nbytes == 0)
			break ;
		b->offset = 0;
	}
	b->total_len += ft_strlen_c(b->buff + b->offset, '\n') + 1;
	line = expand_line(b, line);
	b->offset = b->offset + ft_strlen_c(b->buff + b->offset, '\n') + 1;
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buff	buffer;
	char			*new_line;

	new_line = make_next_line(fd, &buffer);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}
