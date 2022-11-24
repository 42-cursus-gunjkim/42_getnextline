#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd = open("test", O_RDONLY);
	for (int i=0; i<12;i++)
		printf("%s", get_next_line(fd));
}