/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:57:04 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/28 15:02:39 by gunjkim          ###   ########.fr       */
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

static void	lst_del(t_node **head, int fd)
{
	t_node	*curr;
	t_node	*tmp;

	curr = *head;
	if (curr -> fd == fd)
	{
		*head = curr->next;
		free(curr);
		return ;
	}
	while (curr->next->fd != fd)
		curr = curr->next;
	tmp = curr->next;
	curr->next = tmp->next;
	free(tmp);
}

static char	*make_next_line(t_node *head, int fd, t_buff *b)
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
				lst_del(&head, fd);
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

static t_node	*search_insert(t_node **head,int fd)
{
	t_node	*new_node;
	t_node	*tmp;

	tmp = *head;
	if (tmp == NULL)
	{
		new_node = (t_node *)malloc(sizeof(t_node));
		if (new_node == NULL)
			return (NULL);
		new_node->fd = fd;
		new_node->next = NULL;
		new_node->buff.buff[0] = '\0';
		new_node->buff.offset = 0;
		*head = new_node;
		return (new_node);
	}
	while (tmp->next == NULL)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp -> next;
	}
	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node -> fd = fd;
	new_node->next = NULL;
	new_node->buff.buff[0] = '\0';
	new_node->buff.offset = 0;
	tmp -> next = new_node;
	return (new_node);
}

char	*get_next_line(int fd)
{
	static t_node	*head;
	t_node			*fd_node;
	char			*new_line;

	if (fd < 0)
		return (NULL);
	fd_node = search_insert(&head, fd);
	if (fd_node == NULL)
		return (NULL);
	fd_node->buff.total_len = 0;
	new_line = make_next_line(head, fd, &(fd_node->buff));
	return (new_line);
}
