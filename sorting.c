/*
** sorting.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 21:14:37 2016 Arthur Baurens
** Last update Sun Dec  4 21:41:20 2016 Arthur Baurens
*/

#include "my_ls.h"

static int	swap_elems(t_flist **list, t_flist *e1, t_flist *e2)
{
  if (*list == e1)
    *list = e2;
  e1->next = e2->next;
  e2->prev = e1->prev;
  e1->prev = e2;
  e2->next = e1;
  if (e1->next)
    e1->next->prev = e1;
  if (e2->prev)
    e2->prev->next = e2;
  return (0);
}

static void	ls_sort(t_flist **list, char reverse)
{
  t_flist	*cur;
  t_flist	*sec;
  char		sorted;

  sorted = 0;
  while (!sorted)
    {
      sorted = 1;
      cur = *list;
      while (cur && cur->next)
	{
	  sec = cur->next;
	  if ((!reverse && my_strcmp(cur->name, sec->name) > 0) ||
	      (reverse && my_strcmp(cur->name, sec->name) < 0))
	    sorted = swap_elems(list, cur, sec);
	  else
	    cur = cur->next;
	}
    }
}

static void 	time_sort(t_flist **list, char reverse)
{
  t_flist	*cur;
  t_flist	*sec;
  char		sorted;

  sorted = 0;
  while (!sorted)
    {
      sorted = 1;
      cur = *list;
      while (cur && cur->next)
	{
	  sec = cur->next;
	  if ((!reverse && (cur->file.st_ctime - sec->file.st_ctime) < 0) ||
	      (reverse && (cur->file.st_ctime - sec->file.st_ctime) > 0))
	    sorted = swap_elems(list, cur, sec);
	  else
	    cur = cur->next;
	}
    }
}

void	sort_list(t_flist **list, t_ls *my_ls)
{
  if (str_contains('t', my_ls->args))
    time_sort(list, str_contains('r', my_ls->args));
  else
    ls_sort(list, str_contains('r', my_ls->args));
}
