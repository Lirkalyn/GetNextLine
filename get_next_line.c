/*
** EPITECH PROJECT, 2019
** get next line
** File description:
** next-desu
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char *cut_buff(char *buff, int pos)
{
    char *tmp_buff;
    int len;
    int size;
    int i;

    for (len = 0; buff[len] != '\0'; len++);
    size = len - pos;
    tmp_buff = (char *)malloc((size) * sizeof(char));
    tmp_buff[(size - 1)] = '\0';
    for (i = 0; buff[(pos + i + 1)] != '\0'; i++)
        tmp_buff[i] = buff[(pos + i + 1)];
    return tmp_buff;
}

char *to_display(char *buff, int pos)
{
    char *tmp_display;

    tmp_display = (char *)malloc((pos + 1) * sizeof(char));
    tmp_display[pos] = '\0';
    for (int i = 0; i < pos; i++)
        tmp_display[i] = buff[i];
    return tmp_display;
}

char *save_buff(char *buffer, char *buff, int *bool1, int opt)
{
    char *tmp_buffer;
    int len = 0;
    int len2 = 0;
    int i;
    int size;

    if (opt == 1)
        *bool1 += 1;
    for (len = 0; buffer[len] != '\0'; len++);
    for (len2 = 0; buff[len2] != '\0'; len2 += 1);
    size = (len + len2);
    tmp_buffer = (char *)malloc((size + 1) * sizeof(char));
    tmp_buffer[size] = '\0';
    for (i = 0; i < len2; i++)
        tmp_buffer[i] = buff[i];
    for (int j = 0; i < size; i++)
        tmp_buffer[i] = buffer[j++];
    if ((opt == 1) && (tmp_buffer[0] == '\0'))
        *bool1 += 1;
    return tmp_buffer;
}

int n_fd(char *buffer)
{
    int i;

    for (i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == '\n')
            return i;
    return -1;
}

char *get_next_line(int fd)
{
    static char *buff = "\0";
    static int bool1 = 0;
    int pos = 0;
    char *buffer = (char *)malloc((READ_SIZE + 1) * sizeof(char));
    char *display;

    if (buffer == NULL)
        return NULL;
    buffer[READ_SIZE] = '\0';
    if ((fd < 0) || (read(fd, buffer, READ_SIZE) <= 0 && n_fd(buff) == -1)) {
        display = save_buff(buffer, buff, &bool1, 1);
        return (bool1 == 1) ? display : NULL;
    }
    buff = save_buff(buffer, buff, &bool1, 0);
    pos = n_fd(buff);
    if (pos == -1)
        get_next_line(fd);
    if (pos >= 0) {
        display = to_display(buff, pos);
        buff = cut_buff(buff, pos);
        return display;
    }
}