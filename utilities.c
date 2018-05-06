/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:45:37 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/05 19:46:05 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
