/*
** display_file.c for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 21:10:42 2016 Arthur Baurens
** Last update Sun Dec  4 21:42:20 2016 Arthur Baurens
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "my_ls.h"

static void	print_type(int mode)
{
  int		i;
  char		*chars;
  char		masks[7];

  i = 0;
  chars = "-dlcbps";
  masks[i++] = S_ISREG(mode);
  masks[i++] = S_ISDIR(mode);
  masks[i++] = S_ISLNK(mode);
  masks[i++] = S_ISCHR(mode);
  masks[i++] = S_ISBLK(mode);
  masks[i++] = S_ISFIFO(mode);
  masks[i++] = S_ISSOCK(mode);
  while (--i > 0 && !masks[i]);
  write(1, &chars[i], 1);
}

static void 	print_permissions(int mode)
{
  int		i;
  char		*chars;
  int		masks[9];

  i = -1;
  chars = "-rwx";
  print_type(mode);
  masks[0] = S_IRUSR;
  masks[1] = S_IWUSR;
  masks[2] = S_IXUSR;
  masks[3] = S_IRGRP;
  masks[4] = S_IWGRP;
  masks[5] = S_IXGRP;
  masks[6] = S_IROTH;
  masks[7] = S_IWOTH;
  masks[8] = S_IXOTH;
  while (++i < 9)
    write(1, &chars[(mode & masks[i] ? 1 : 0) * (i % 3 + 1)], 1);
  write(1, " ", 1);
}

static void	display_stats(t_stat *file)
{
  char		*tmp;
  struct passwd	*user;
  struct group	*group;

  user = getpwuid(file->st_uid);
  group = getgrgid(file->st_gid);
  print_permissions(file->st_mode);
  my_putnbr(file->st_nlink, " ", 0);
  my_putstr(user->pw_name, " ", 0);
  my_putstr(group->gr_name, " ", 0);
  my_putnbr(file->st_size, " ", 5);
  tmp = ctime(&file->st_mtime);
  tmp = my_strncat(NULL, &tmp[4], 16 - 4);
  my_putstr(tmp, " ", 0);
}

void	display_file(t_ls *my_ls, t_flist *file)
{
  char	*lnk;
  long	r;

  if (str_contains('l', my_ls->args))
    display_stats(&file->file);
  my_putstr(file->name, NULL, 0);
  if (S_ISLNK(file->file.st_mode) && str_contains('l', my_ls->args))
    {
      my_putstr(" -> ", NULL, 0);
      if ((lnk = malloc(sizeof(char) * file->file.st_size + 1)) == NULL)
	return ;
      if ((r = readlink(file->path, lnk, file->file.st_size + 1)) == -1)
	return;
      lnk[r] = '\0';
      my_putstr(lnk, "\n", 0);
    }
  else
    my_putstr("\n", NULL, 0);
}
