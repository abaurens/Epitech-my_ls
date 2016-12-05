/*
** display_dir.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 20:52:32 2016 Arthur Baurens
** Last update Sun Dec  4 23:04:04 2016 Arthur Baurens
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "my_ls.h"

static int	display_dir_size(t_ls *my_ls, t_flist *content)
{
  int		count;

  count = 0;
  while (content != NULL)
    {
      if (content->name[0] != '.' || str_contains('a', my_ls->args))
	count += content->file.st_blocks;
      content = content->next;
    }
  my_putstr("total", " ", 0);
  my_putnbr((count + 1) / 2, "\n", 0);
  return (0);
}

static t_flist	*get_dir_content(t_ls *my_ls, t_flist *dir)
{
  char		*tmp;
  char		*path;
  t_dirent	*cur;
  t_flist	*content;
  t_stat	file;

  content = NULL;
  if (dir->dir == NULL)
    return (NULL);
  while ((cur = readdir(dir->dir)) != NULL)
    {
      if (dir->path == NULL)
	tmp = my_strncat(dir->name, "/", -1);
      else
	tmp = my_strncat(dir->path, "/", -1);
      path = my_strncat(tmp, cur->d_name, -1);
      free(tmp);
      if (lstat(path, &file) < 0)
	write(2, "ERROR 2\n", 8);
      if (cur->d_name[0] != '.' || str_contains('a', my_ls->args))
	put_in_list(&content, path, cur->d_name);
      free(path);
    }
  sort_list(&content, my_ls);
  return (content);
}

static void	add_subfolder(t_flist *dir, t_flist *content, t_flist **subs)
{
  char		*tmp;
  char		*path;

  if (content->type == E_DIRECTORY &&
      my_strcmp(".", content->name) != 0 &&
      my_strcmp("..", content->name) != 0)
    {
      if (dir->path == NULL)
	{
	  if (dir->name[str_len(dir->name) - 1] == '/')
	    tmp = my_strncat(dir->name, NULL, -1);
	  else
	    tmp = my_strncat(dir->name, "/", -1);
	}
      else
	tmp = my_strncat(dir->path, "/", -1);
      path = my_strncat(tmp, content->name, -1);
      free(tmp);
      put_in_list(subs, path, content->name);
      free(path);
    }
}

static void	display_dir_content(t_ls *my_ls, t_flist *dir)
{
  char		v;
  t_flist	*content;
  t_flist	*subs;

  subs = NULL;
  v = 1;
  content = get_dir_content(my_ls, dir);
  if (str_contains('R', my_ls->args))
    display_dir_size(my_ls, content);
  while (content != NULL)
    {
      display_file(my_ls, content);
      if (str_contains('R', my_ls->args))
	add_subfolder(dir, content, &subs);
      rm_elem_in_list(&content, content, 0);
    }
  while (subs != NULL)
    {
      display_directory(my_ls, subs, 1, &v);
      subs = subs->next;
    }
}

void	display_directory(t_ls *my_ls, t_flist *dir, char multiple, char *frst)
{
  char	v;

  v = open_directory(dir, dir->path == NULL ? dir->name : dir->path);
  if (*frst && v)
    my_putstr("\n", NULL, 0);
  else if (v)
    (*frst)++;
  if (v && (multiple || str_contains('R', my_ls->args)))
    my_putstr(dir->path == NULL ? dir->name : dir->path, ":\n", 0);
  if (str_contains('d', my_ls->args))
    my_putstr(dir->name, "\n", 0);
  else
    display_dir_content(my_ls, dir);
}
