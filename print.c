/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 14:29:38 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 18:01:09 by ckrommen         ###   ########.fr       */
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
	if (list == ptr && ((*info).re || (*info).dc > 1) && list->perm)
		ft_printf("%s:\n", list->path);
	print_blocks(list, info);
	while (list)
	{
		list->perm ? INFO : ERROR;
		list->is_dir = (list->sub_dir) ? true : false;
		list = list->next;
	}
	(*info).pc++;
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
	if (list == ptr && ((*info).re || (*info).dc > 1) && list->perm)
		ft_printf("%s:\n", list->path);
	print_blocks(list, info);
	while (list)
	{
		list->perm ? INFO : ERROR;
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
