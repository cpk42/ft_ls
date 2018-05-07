/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:19:05 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 20:57:17 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	build_path(char *str, t_dir *list)
{
	ft_bzero(str, 1024);
	ft_strcat(str, (*list).path);
	ft_strcat(str, "/");
	ft_strcat(str, (*list).name);
}

void	print_perms(struct stat stat)
{
	if (S_ISLNK(stat.st_mode))
		ft_putchar('l');
	else
		ft_putchar((S_ISDIR(stat.st_mode)) ? 'd' : '-');
	ft_putchar((stat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((stat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((stat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((stat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((stat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((stat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((stat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((stat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((stat.st_mode & S_IXOTH) ? 'x' : '-');
}

void	print_time(char *str)
{
	char	format[1024];
	int		i;
	int		x;
	int		colon;

	ft_bzero(format, 1024);
	i = 0;
	x = 0;
	colon = 0;
	while (str[i] != ' ')
		i++;
	while (str[i] != '\n' && str[i])
	{
		if (str[i] == ':')
			colon++;
		if (colon == 2)
			break ;
		format[x++] = str[i++];
	}
	ft_printf(format);
}

char	*get_info(t_dir *list, t_info *info)
{
	char			path[1024];
	char			str[1024];
	struct stat		stat;
	struct passwd	*pw;
	struct group	*gr;

	ft_bzero(path, 1024);
	ft_bzero(path, sizeof(struct stat));
	build_path(path, list);
	if ((*info).l)
	{
		lstat(path, &stat);
		pw = getpwuid(stat.st_uid);
		gr = getgrgid(stat.st_gid);
		print_perms(stat);
		ft_printf("%4d ", stat.st_nlink);
		ft_printf("%-10s%-10s%6d", pw->pw_name, gr->gr_name, stat.st_size);
		print_time(ctime(&stat.st_mtime));
		ft_printf(" %s", list->name);
		readlink(path, str, 1024);
		if (S_ISLNK(stat.st_mode))
			ft_printf(" -> %s", str);
	}
	return ("");
}

void	print_blocks(t_dir *list, t_info *info)
{
	char		path[1024];
	struct stat	stat;
	int			total;

	total = 0;
	ft_bzero(path, 1024);
	ft_bzero(path, sizeof(struct stat));
	if (info->l && list->perm)
	{
		while (list)
		{
			build_path(path, list);
			lstat(path, &stat);
			total += stat.st_blocks;
			list = (*info).r ? list->prev : list->next;
		}
		ft_printf("total %d\n", total);
	}
}
