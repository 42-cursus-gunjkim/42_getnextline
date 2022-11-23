#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd = open("test",O_RDONLY);
	char *test = get_next_line(fd);
	printf("%s\n", test);
	test = get_next_line(fd);
	printf("%s\n", test);
}
