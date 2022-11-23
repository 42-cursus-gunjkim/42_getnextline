/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/23 14:35:23 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *make_next_line(int fd, t_buff *b)
{
	char	*next_line;
	char	*next_line_tmp;

	next_line = ft_strdup("");
	if (b->offset == 0)
	{
		read(fd, b->buff, BUFFER_SIZE - 1);
		b->buff[BUFFER_SIZE - 1] = '\0';
	}
	while (ft_strchr(b->buff + b->offset, 10) == NULL)
	{
		b->total_len = b->total_len + ft_strlen_c(b->buff, '\0');
		next_line_tmp = (char *)malloc(sizeof(char) *(b->total_len + 1));
		ft_strlcpy(next_line_tmp, next_line, b->total_len + 1);
		ft_strlcat(next_line_tmp, next_line, b->total_len + 1);
		free(next_line);
		next_line = next_line_tmp;
		read(fd, b->buff, BUFFER_SIZE);
		b->offset = 0;
	}
	b->total_len = b->total_len + ft_strlen_c(b->buff + b->offset, '\n') + 1;
	next_line_tmp = (char *)malloc(sizeof(char) *(b->total_len + 1));
	ft_strlcpy(next_line_tmp, next_line, b->total_len + 1);
	ft_strlcat(next_line_tmp, next_line, b->total_len + 1);
	free(next_line);
	next_line = next_line_tmp;
	b->offset = ft_strlen_c(b->buff + b->offset, '\0') + 1;
	return (next_line);
}

char	*get_next_line(int fd)
{
	static t_buff	*buffer;

	buffer = (t_buff *)malloc(sizeof(t_buff));
	if (buffer == NULL)
		return (NULL);
	return (make_next_line(fd, buffer));
}
