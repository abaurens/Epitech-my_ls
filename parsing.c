/*
** parsing.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 20:47:23 2016 Arthur Baurens
** Last update Sun Dec  4 23:16:19 2016 Arthur Baurens
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "my_ls.h"

static void	parse_flags(const char *flags, char **args)
{
  int		i;
  char		*tmp;

  i = -1;
  while (flags && flags[++i])
    {
      if (!str_contains(flags[i], "lrRtda"))
	{
	  print_flag_err_msg(flags[i]);
	  exit(84);
	}
      if (!str_contains(flags[i], *args))
	{
	  tmp = *args;
	  *args = my_strncat(tmp, &flags[i], str_len(tmp) + 1);
	  free(tmp);
	}
    }
}

static int	put_in_lists(const char *name, t_flist **files)
{
  t_flist	*file;

  file = malloc(sizeof(t_flist));
  if (stat(name, &file->file) < 0)
    {
      my_puterror(get_file_err_msg(), my_strncat(name, "'", -1), errno);
      return (free_returner(file, 1));
    }
  file->type = ((S_ISDIR(file->file.st_mode)) == E_DIRECTORY);
/*if ((file->type = S_ISDIR(file->file.st_mode)) == E_DIRECTORY)
    {
      if ((file->dir = opendir(name)) == NULL)
	{
	  my_puterror(get_dir_err_msg(), my_strncat(name, "'", -1), errno);
	  return (free_returner(file, 1));
	}
}*/
  file->path = NULL;
  file->name = name;
  file->next = *files;
  file->prev = NULL;
  if (file->next)
    file->next->prev = file;
  *files = file;
  return (1);
}

char	*parse_entry(int ac, char **av, t_flist **files)
{
  char	*res;
  int	th_lst_len;

  res = NULL;
  th_lst_len = 0;
  while (--ac > 0)
    {
      if (av[ac][0] == '-')
	parse_flags(&av[ac][1], &res);
      else
	th_lst_len += put_in_lists(av[ac], files);
    }
  if (*files == NULL && th_lst_len == 0)
    {
      *files = malloc(sizeof(t_flist));
      (*files)->path = NULL;
      (*files)->name = ".";
      (*files)->next = NULL;
      (*files)->prev = NULL;
      (*files)->type = E_DIRECTORY;
      (*files)->dir = opendir(".");
      return (res);
    }
  return (res);
}
