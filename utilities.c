/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:45:37 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 20:48:46 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	get_time(t_dir *head)
{
	char		path[1024];
	struct stat	stat;

	ft_bzero(path, 1024);
	ft_bzero(&stat, sizeof(struct stat));
	build_path(path, head);
	lstat(path, &stat);
	return (stat.st_mtime);
}

char	*get_file(char *str)
{
	char *ptr;

	ptr = str;
	while (ft_strchr(ptr, '/'))
	{
		ptr = ft_strchr(ptr, '/');
		ptr++;
	}
	return (ptr);
}

int		check_arg(char *str)
{
	struct stat	stat;
	int			ret;

	lstat(str, &stat);
	if (S_ISDIR(stat.st_mode))
		ret = 1;
	else if (!S_ISREG(stat.st_mode))
		ret = 0;
	else if (S_ISREG(stat.st_mode))
		ret = 0;
	else
		ret = 0;
	return (ret);
}

int		count_dir(char **argv)
{
	int	i;
	int	count;

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
	while (head)
	{
		if (head->is_dir)
			return (1);
		head = head->next;
	}
	return (0);
}
