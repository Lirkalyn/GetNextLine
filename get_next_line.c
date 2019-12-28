/*
** EPITECH PROJECT, 2019
** get next line
** File description:
** next-desu
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
    char *buffer = (char *)malloc((READ_SIZE + 1) * sizeof(char));
    ssize_t check = 0;

    buffer[READ_SIZE] = '\0';
    check = read(fd, buffer, READ_SIZE);
    if (check <= 0)
        return NULL;
    else if (buffer[READ_SIZE - 1] == '\n')
        buffer[READ_SIZE - 1] = '\0';
    return buffer;
}