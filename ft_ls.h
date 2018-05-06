/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:16:37 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/05 19:23:51 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <time.h>
# include "./libft/libft.h"
# define CPC (info->dc > info->pc ? "\n" : "")
# define true 1
# define false 0

typedef int bool;

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
	struct dirent	*d_info;
	struct stat		stat;
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
t_dir				*merge_sort(t_dir *head);
t_dir				*merge(t_dir *first, t_dir *second);

/*
** Struct initialize
*/

t_info				init_info(int argc, int dc);
int					load_flags(t_info *info, char **argv);
t_dir				*init_dir(char *dir_name, char *name, struct stat info, struct dirent *d_info);
void				add_dir(t_dir **head, char *dir, char *name, struct stat info, struct dirent *d_info);

/*
** Extra utilities
*/

t_dir				*get_end(t_dir *list);
char				*get_info(t_dir *list, t_info *info);
char				*get_file(char *str);
void				rm_dir(t_info *info);
void				build_path(char *str, t_dir *list);
int					count_dir(char **argv);
int					check_subdir(t_dir *head);
int					check_arg(char *str);

/*
** Display information
*/

t_dir				*throw_err(char *msg, int i, t_info *info);
void				print_list(t_dir *list, t_info *info);
void				rev_print_list(t_dir *list, t_info *info);
void				print_nonfile(char **argv, t_info *info);
void				print_reg(char **argv, t_info *info);
void				print_errors(char **argv, t_info *info, int i);
void				print_perms(struct stat stat);
void				print_time(char *time);
void				print_blocks(t_dir *list, t_info *info);

#endif
