#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    const char *filename = "out.txt";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if(dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2 problem");
        close(fd);
        return 1;
    }
}