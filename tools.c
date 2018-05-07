/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:15:22 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 20:31:48 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		load_flags(t_info *info, char **argv)
{
	int	i;
	int	x;

	i = 0;
	while (argv[++i] && argv[i][0] == '-')
	{
		x = 1;
		while (argv[i][x])
		{
			if (argv[i][x] == 'R')
				info->re = 1;
			else if (argv[i][x] == 'a')
				info->a = 1;
			else if (argv[i][x] == 't')
				info->t = 1;
			else if (argv[i][x] == 'r')
				info->r = 1;
			else if (argv[i][x] == 'l')
				info->l = 1;
			else
				return (-1);
			x++;
		}
	}
	return (i);
}

t_info	init_info(int argc, int dc)
{
	t_info	info;

	info.re = 0;
	info.a = 0;
	info.l = 0;
	info.r = 0;
	info.t = 0;
	info.is_err = 0;
	info.dc = dc;
	info.pc = 0;
	info.argc = argc;
	ft_bzero(info.dir_name, 256);
	ft_bzero(info.perm, 256);
	return (info);
}

t_dir	*init_dir(char *dir_name, char *name)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	ft_bzero(dir->path, 256);
	ft_bzero(dir->name, 256);
	ft_strcpy(dir->path, dir_name);
	ft_strcpy(dir->name, name);
	dir->perm = 1;
	dir->is_dir = 0;
	dir->next = NULL;
	dir->prev = NULL;
	dir->sub_dir = NULL;
	return (dir);
}

t_dir	*add_dir(t_dir **head, char *dir, char *name)
{
	t_dir	*elem;
	t_dir	*ptr;

	if (*head)
	{
		elem = init_dir(dir, name);
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = elem;
		elem->prev = ptr;
	}
	else
		*head = init_dir(dir, name);
	return (NULL);
}

t_dir	*add_badperm(t_dir **head, char *dir, char *name)
{
	t_dir	*elem;
	t_dir	*ptr;

	if (*head)
	{
		elem = init_dir(dir, name);
		elem->perm = 0;
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = elem;
		elem->prev = ptr;
	}
	else
	{
		*head = init_dir(dir, name);
		(*head)->perm = 0;
	}
	return (*head);
}
