/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:09 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/22 17:32:45 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# if BUFFER_SIZE < 1
#  error INVALID BUFFER_SIZE!
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_buff
{
	char	buff[BUFFER_SIZE];
	size_t	offset;
	size_t	total_len;
}	t_buff;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif