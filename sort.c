/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:21:13 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 21:01:15 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*split(t_dir *head)
{
	t_dir	*fast;
	t_dir	*slow;
	t_dir	*temp;

	fast = head;
	slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	temp = slow->next;
	slow->next = NULL;
	return (temp);
}

t_dir	*normal_merge(t_dir *first, t_dir *second)
{
	if (!first)
		return (second);
	if (!second)
		return (first);
	if (ALPHA)
	{
		first->next = normal_merge(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return (first);
	}
	else
	{
		second->next = normal_merge(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return (second);
	}
}

t_dir	*time_merge(t_dir *first, t_dir *second)
{
	if (!first || !second)
		return (!second ? first : second);
	if ((get_time(first) == get_time(second)) ? ALPHA : TIME)
	{
		first->next = time_merge(first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return (first);
	}
	else
	{
		second->next = time_merge(first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return (second);
	}
}

t_dir	*merge_sort(t_dir *head, t_info *info)
{
	t_dir	*second;

	if (!head || !head->next)
		return (head);
	second = split(head);
	head = merge_sort(head, info);
	second = merge_sort(second, info);
	return (info->t ? time_merge(head, second) : normal_merge(head, second));
}

void	rm_dir(t_info *info)
{
	int		i;
	char	*str;

	str = info->dir_name;
	i = ft_strlen(str) - 1;
	while (str[i] != '/' && str[i])
		str[i--] = '\0';
	str[i] = '\0';
}
