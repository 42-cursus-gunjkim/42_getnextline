#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd = open("test", O_RDONLY);
	for (int i=0; i<10;i++)
		printf("%s",get_next_line(fd));
}