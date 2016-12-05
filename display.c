/*
** display.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 21:13:18 2016 Arthur Baurens
** Last update Sun Dec  4 21:41:10 2016 Arthur Baurens
*/
#include "my_ls.h"

void	my_putstr(const char *str, const char *app, int n)
{
  int	len;

  len = str_len(str);
  while (--n >= len)
    write(1, " ", 1);
  write(1, str, len);
  if (app != NULL)
    my_putstr(app, NULL, 0);
}

void		my_putnbr(long int nb, const char *app, int n)
{
  char		d;
  int		len;
  long int	tmp;

  len = 1;
  tmp = nb;

  while (tmp /= 10)
    len++;
  while (--n >= len)
    write(1, " ", 1);
  if (nb / 10 > 0)
    my_putnbr(nb / 10, 0, 0);
  d = nb % 10 + '0';
  write(1, &d, 1);
  if (app != NULL)
    my_putstr(app, NULL, 0);
}
