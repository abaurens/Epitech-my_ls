/*
** list.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 20:52:38 2016 Arthur Baurens
** Last update Sun Dec  4 22:43:37 2016 Arthur Baurens
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "my_ls.h"

void		put_in_list(t_flist **files, const char *path, const char *name)
{
  t_flist	*file;

  file = malloc(sizeof(t_flist));
  if (lstat(path, &file->file) < 0)
    {
      my_puterror(get_file_err_msg(), my_strncat(path, "'", -1), errno);
      free(file);
      return ;
    }
  file->type = ((S_ISDIR(file->file.st_mode)) == E_DIRECTORY);
/*if ((file->type = S_ISDIR(file->file.st_mode)) == E_DIRECTORY)
    {
      if ((file->dir = opendir(path)) == NULL)
	{
	  my_puterror(get_dir_err_msg(), my_strncat(path, "'", -1), errno);
	  free(file);
	  return ;
	}
}*/
  file->path = my_strncat(NULL, path, -1);
  file->name = name;
  file->next = *files;
  file->prev = NULL;
  if (file->next)
    file->next->prev = file;
  *files = file;
}

void	rm_elem_in_list(t_flist **list, t_flist *elem, char close_dir)
{
  if (elem == *list)
    *list = elem->next;
  if (elem->next)
    elem->next->prev = elem->prev;
  if (elem->prev)
    elem->prev->next = elem->next;
  if (elem->type == E_DIRECTORY && close_dir)
    closedir(elem->dir);
  free(elem->path);
  free(elem);
}

int		list_size(t_flist *list)
{
  int	i;

  i = 0;
  while (list != NULL)
    {
      i++;
      list = list->next;
    }
  return (i);
}
