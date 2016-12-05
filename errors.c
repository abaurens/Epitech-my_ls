/*
** errors.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 20:27:14 2016 Arthur Baurens
** Last update Sun Dec  4 23:16:37 2016 Arthur Baurens
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "my_ls.h"

char	*get_file_err_msg()
{
  return ("my_ls: cannot access '");
}

char	*get_dir_err_msg()
{
  return ("my_ls: cannot open directory '");
}

void	print_flag_err_msg(char c)
{
  write(2, "my_ls: invalid option -- '", 26);
  write(2, &c, 1);
  write(2, "'\n", 2);
}

void	my_puterror(const char *str, const char *err, int error)
{
  write(2, str, str_len(str));
  errno = error;
  perror(err);
}

int	free_returner(void *ptr, int ret)
{
  free(ptr);
  return (ret);
}
