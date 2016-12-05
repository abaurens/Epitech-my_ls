/*
** string.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 21:15:21 2016 Arthur Baurens
** Last update Sun Dec  4 21:41:24 2016 Arthur Baurens
*/

#include <stdlib.h>

int	str_len(const char *str)
{
  int	i;

  i = -1;
  while (str && str[++i]);
  return (i * (str != NULL));
}

char	str_contains(char c, const char *str)
{
  int	i;

  i = -1;
  while (str && str[++i])
    {
      if (str[i] == c)
	return (1);
    }
  return (0);
}

char	*my_strncat(const char *s1, const char *s2, int n)
{
  int	i;
  int	j;
  int	l;
  char	*res;


  l = str_len(s1) + str_len(s2);
  if (n >= 0 || l < n)
    l = n;
  if (l == 0 || (res = malloc(sizeof(char) * l + 1)) == NULL)
    return (NULL);
  res[l] = '\0';
  i = 0;
  while (s1 && s1[i] && i < l)
    {
      res[i] = s1[i];
      i++;
    }
  j = -1;
  while (s2 && s2[++j] && i + j < l)
    res[i + j] = s2[j];
  return (res);
}

int		my_strcmp(const char *s1, const char *s2)
{
  int	i;

  i = 0;
  while (s1 && s2)
    {
      if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
      else if (s1[i] == '\0')
	return (0);
      i++;
    }
  return (0);
}
