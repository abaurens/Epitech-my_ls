/*
** main.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 20:54:14 2016 Arthur Baurens
** Last update Sun Dec  4 23:00:44 2016 Arthur Baurens
*/

#include <errno.h>
#include "my_ls.h"

char	open_directory(t_flist *file, const char *path)
{
  if (file->type == E_DIRECTORY && path != NULL)
    {
      if ((file->dir = opendir(path)) == NULL)
	{
	  my_puterror(get_dir_err_msg(), my_strncat(path, "'", -1), errno);
	  return (0);
	}
    }
  return (1);
}

static void	list_dirs(t_ls *my_ls, int lst_size)
{
  char		first;

  first = 1;
  while (my_ls->files != NULL && !str_contains('d', my_ls->args))
    {
      if (my_ls->files->type == E_DIRECTORY)
	display_directory(my_ls, my_ls->files, lst_size > 1, &first);
      rm_elem_in_list(&my_ls->files, my_ls->files, 1);
    }
}

int		main(int ac, char **av)
{
  int		lst_size;
  t_ls		my_ls;
  t_flist	*lst;

  my_ls.files = NULL;
  my_ls.args = parse_entry(ac, av, &my_ls.files);
  lst_size = list_size(my_ls.files);
  sort_list(&my_ls.files, &my_ls);
  lst = my_ls.files;
  while (lst != NULL)
    {
      if (lst->type == E_FILE || str_contains('d', my_ls.args))
	{
	  display_file(&my_ls, lst);
	  if (!(lst->next))
	    my_putstr("\n", 0, 0);
	}
      lst = lst->next;
    }
  list_dirs(&my_ls, lst_size);
  return (0);
}
