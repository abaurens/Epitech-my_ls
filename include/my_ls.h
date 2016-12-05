/*
** my_ls.h for ls in /home/baurens/Work/Tek1/Projects/PSU/PSU_2016_my_ls/include/
**
** Made by Arthur Baurens
** Login   <arthur.baurens@epitech.eu>
**
** Started on  Sun Dec  4 20:52:51 2016 Arthur Baurens
** Last update Sun Dec  4 23:15:48 2016 Arthur Baurens
*/

#ifndef MY_LS_H_
# define MY_LS_H_

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>

typedef	struct dirent	t_dirent;
typedef struct stat	t_stat;
typedef struct passwd	t_group;
typedef struct group	t_passwd;

typedef enum		e_file_type
{
  E_FILE, E_DIRECTORY
}			t_file_type;

typedef struct		s_flist
{
  struct s_flist	*next;
  struct s_flist	*prev;
  char 			*path;
  const char		*name;
  t_file_type		type;
  t_stat		file;
  DIR			*dir;
}			t_flist;

typedef struct	s_ls
{
  const char	*args;
  t_flist	*files;
}		t_ls;

/*
**	parsing.h
*/
char	*parse_entry(int, char **, t_flist **);

/*
**	string.c
*/
int	str_len(const char *);
char	str_contains(char, const char *);
char	*my_strncat(const char *, const char *, int);
int	my_strcmp(const char *, const char *);
int	my_lscmp(const char *, const char *, char);

/*
** display_dir.c
*/
void	display_directory(t_ls *, t_flist *, char, char *);

/*
**	display_file.c
*/
void	display_file(t_ls *, t_flist *);

/*
**	display.c
*/
void	my_putstr(const char *, const char *, int);
void	my_putnbr(long int, const char *, int);

/*
**	list.c
*/
int	list_size(t_flist *);
void	rm_elem_in_list(t_flist **, t_flist *, char);
void	put_in_list(t_flist **, const char *, const char *);

/*
**	sorting.c
*/
void	sort_list(t_flist **, t_ls *my_ls);

/*
**	errors.c
*/
char	*get_dir_err_msg();
char	*get_file_err_msg();
void	print_flag_err_msg(char c);
void	my_puterror(const char *, const char *, int);
int	free_returner(void *, int);

/*
**	main.c
*/
char	open_directory(t_flist *, const char *);

#endif /* !MY_LS_H_ */
