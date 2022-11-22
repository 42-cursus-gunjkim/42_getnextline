/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:10:06 by gunjkim           #+#    #+#             */
/*   Updated: 2022/11/22 13:14:45 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd1;
	int fd2;
	char c1[10];
	char c2[10];

	fd1 = open("test", O_RDONLY);
	fd2 = open("test", O_RDONLY);
	read(fd1, &c1, 3);
	read(fd2, &c2, 4);
	printf("%s  %s", c1 ,c2);
}
