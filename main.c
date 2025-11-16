#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"


// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl_test

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); 
    }

    close(fd);
    return 0;
}
