/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:15:22 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/05 17:19:30 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		load_flags(t_info *info, char **argv)
{
	int i;
	int x;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		x = 1;
		while (argv[i][x])
		{
			if (argv[i][x] == 'R')
				info->re = true;
			else if (argv[i][x] == 'a')
				info->a = true;
			else if (argv[i][x] == 't')
				info->t = true;
			else if (argv[i][x] == 'r')
				info->r = true;
			else if (argv[i][x] == 'l')
				info->l = true;
			else
				return (-1);
			x++;
		}
		i++;
	}
	return (i);
}

t_info	init_info(int argc, int dc)
{
	t_info info;

	info.re = false;
	info.a = false;
	info.l = false;
	info.r = false;
	info.t = false;
	info.is_err = false;
	info.dc = dc;
	info.pc = 0;
	info.argc = argc;
	ft_bzero(info.dir_name, 256);
	ft_bzero(info.perm, 256);
	return (info);
}

t_dir	*init_dir(char *dir_name, char *name,  struct stat info, struct dirent *d_info)
{
	t_dir *dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	ft_bzero(dir->path, 256);
	ft_bzero(dir->name, 256);
	ft_strcpy(dir->path, dir_name);
	ft_strcpy(dir->name, name);
	ft_bzero(&(dir->stat), sizeof(struct stat));
	dir->stat = info;
	dir->d_info = d_info;
	dir->is_dir = false;
	dir->next = NULL;
	dir->prev = NULL;
	dir->sub_dir = NULL;
	return (dir);
}

void	add_dir(t_dir **head, char *dir, char *name, struct stat info, struct dirent *d_info)
{
	t_dir	*elem;
	t_dir	*ptr;

	if (*head)
	{
		elem = init_dir(dir, name, info, d_info);
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = elem;
		elem->prev = ptr;
	}
	else
		*head = init_dir(dir, name, info, d_info);
}

int		count_dir(char **argv)
{
	int i;
	int count;

	count = 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int		check_subdir(t_dir *head)
{
	int i;

	i = 0;
	while (head)
	{
		if (head->is_dir)
			i = 1;
		head = head->next;
	}
	return (i);
}
