/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:16:37 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 20:47:02 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <stdbool.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <time.h>
# include "./libft/libft.h"
# define F_NAME (file->d_name)
# define PERM (info->re || info->dc >= 2)
# define CPC (info->dc > info->pc ? "\n" : "")
# define TIME (get_time(first) > get_time(second))
# define DOUBLE (argv[i][0] == '-' && argv[i][1] == '-')
# define ALPHA (ft_strcmp(first->name, second->name) < 0)
# define C_HIDDEN (ft_strncmp(".", file->d_name, 1) != 0)
# define ERROR (int)throw_err(get_file(list->name), 2, info, list)
# define HIDDEN (F_NAME[0] == '.' && F_NAME[1] != '.' && F_NAME[1])
# define ARGS(c) (*msg == 'R' || *msg == 'a' || *msg == 'l' || *msg == 'r')
# define INFO ft_printf("%s\n", info->l ? get_info(list, info) : list->name)
# define ILLEGAL "ls: illegal option -- %c\nusage: ls [-altrR] [file ...]\n"

typedef struct		s_info
{
	bool			is_err;
	bool			re;
	bool			a;
	bool			l;
	bool			r;
	bool			t;
	int				argc;
	int				dc;
	int				pc;
	char			perm[256];
	char			dir_name[256];
}					t_info;

typedef struct		s_dir
{
	char			path[256];
	char			name[256];
	bool			is_dir;
	bool			perm;
	struct s_dir	*next;
	struct s_dir	*prev;
	struct s_dir	*sub_dir;
}					t_dir;

/*
** Main functions
*/

void				sort_list(t_dir **list);
t_dir				*ft_ls(t_info *info, t_dir **list);

/*
** List sort
*/

t_dir				*split(t_dir *head);
t_dir				*merge_sort(t_dir *head, t_info *info);
t_dir				*normal_merge(t_dir *first, t_dir *second);
t_dir				*time_merge(t_dir *first, t_dir *second);

/*
** Struct initialize
*/

t_info				init_info(int argc, int dc);
int					load_flags(t_info *info, char **argv);
t_dir				*init_dir(char *dir_name, char *name);
t_dir				*add_dir(t_dir **head, char *dir, char *name);
t_dir				*add_badperm(t_dir **head, char *dir, char *name);

/*
** Extra utilities
*/

t_dir				*get_end(t_dir *list);
char				*get_info(t_dir *list, t_info *info);
char				*get_file(char *str);
void				rm_dir(t_info *info);
void				free_list(t_dir **list);
void				build_path(char *str, t_dir *list);
int					count_dir(char **argv);
int					check_subdir(t_dir *head);
int					check_arg(char *str);
long				get_time(t_dir *head);

/*
** Display information
*/

t_dir				*throw_err(char *msg, int i, t_info *info, t_dir *list);
void				print_list(t_dir *list, t_info *info);
void				rev_print_list(t_dir *list, t_info *info);
void				print_nonfile(char **argv, t_info *info);
void				print_reg(char **argv, t_info *info);
void				print_errors(char **argv, t_info *info, int *i);
void				print_perms(struct stat stat);
void				print_time(char *time);
void				print_blocks(t_dir *list, t_info *info);

#endif
