/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/22 17:36:36 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*make_next_line(int fd, t_buff *b)
{
	char	*next_line;
	char	*next_line_tmp;

	if (b->offset == 0)
		read(fd, b->buff, BUFFER_SIZE);
	while (ft_strchr(b->buff + b->offset, 10) == NULL)
	{
		//전체길이를 계산해서 total_len + 남은길이만큼 할당해서 카피 카피는 offset부터 끝까지
		b->total_len += BUFFER_SIZE - b->offset + 1;
		next_line_tmp = (char *)malloc(sizeof(char) * (b->total_len + 1));
		ft_strlcpy(next_line_tmp, next_line, );
		ft_strjoin
		read(fd, b->buff, BUFFER_SIZE);
		b->offset = 0;
		//다시 read
	}
	//개행까지의 길이를 계산해서 total_len만큼 할당하고 카피
}

char	*get_next_line(int fd)
{
	static t_buff	*buffer;

	buffer = (t_buff *)malloc(sizeof(t_buff));
	if (buffer == NULL)
		return (NULL);
}
