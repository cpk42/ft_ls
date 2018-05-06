/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:29:38 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/05 17:59:07 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*get_end(t_dir *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void	print_list(t_dir *list, t_info *info)
{
	t_dir	*ptr;

	ptr = list;
	if (list == ptr && ((*info).re || (*info).dc > 1))
		ft_printf("%s:\n", list->path);
	print_blocks(list, info);
	while (list)
	{
		ft_printf("%s%s\n", get_info(list, info), list->name);
		list->is_dir = (list->sub_dir) ? true : false;
//		ft_printf("%s %s%d %d\n", (*list).name, (*ptr).name, (*info).re, list->is_dir);
		list = list->next;
	}
	(*info).pc++;
//	ft_printf("%d%d\n", info->pc, info->dc);
	if (!check_subdir(ptr) && ((*info).pc < (*info).dc))
		ft_putendl("");
	while (ptr)
	{
		if (ptr->is_dir)
		{
			ft_putendl("");
			print_list(ptr->sub_dir, info);
		}
		ptr = ptr->next;
	}
}

void	rev_print_list(t_dir *list, t_info *info)
{
	t_dir	*ptr;

	list = get_end(list);
	ptr = list;
	if (list == ptr && ((*info).re || (*info).dc > 1))
		ft_printf("%s:\n", list->path);
	print_blocks(list, info);
	while (list)
	{
		ft_printf("%s%s\n", get_info(list, info), list->name);
		list->is_dir = (list->sub_dir) ? true : false;
		list = list->prev;
	}
	(*info).pc++;
	if (!check_subdir(ptr) && ((*info).pc < (*info).dc))
		ft_putendl("");
	while (ptr)
	{
		if (ptr->is_dir)
		{
			ft_putendl("");
			rev_print_list(ptr->sub_dir, info);
		}
		ptr = ptr->prev;
	}
}
