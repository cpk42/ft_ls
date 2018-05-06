/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:19:20 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/05 19:47:10 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//void	print_perms(t_dir *list)
//{
//	while ()
//}

t_dir	*throw_err(char *msg, int i, t_info *info)
{
	if (i == -1)
	{
		(*info).dc--;
		ft_printf("ls: %s: No such file or directory\n", msg);
	}
	else if (i == 0)
	{
		while (*msg == '-' || *msg == 'a' || *msg == 'l' || *msg == 'r' ||
			   *msg == 'R' || *msg == 't')
			msg++;
		ft_printf("ls: illegal option -- %c\nusage: ls [-altrR] [file ...]\n", *msg);
	}
	else if (i == 1)
		ft_printf("%s\n", msg);
	else if (i == 2)
	{
		ft_printf("%s%s", info->re ? info->dir_name : "", info->re ? ":\n" : "");
		ft_printf("ls: %s: Permission denied\n%s", get_file(msg), CPC);
		(*info).dc++;
	}
	(*info).pc++;
	return (NULL);
}

void	print_nonfile(char **argv, t_info *info)
{
	struct stat	stat;
	int i;
	int toggle;

	i = 1;
	toggle = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			toggle = 1;
		if (argv[i][0] == '-' && !toggle)
			i++;
		else
		{
			ft_bzero(&stat, sizeof(struct stat));
			lstat(argv[i], &stat);
			if ((!S_ISDIR(stat.st_mode) && (!S_ISREG(stat.st_mode))))
				throw_err(argv[i], -1, info);
			i++;
		}
	}
}

void	print_reg(char **argv, t_info *info)
{
	struct stat	stat;
	int i;
	int toggle;

	i = 1;
	toggle = 0;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			toggle = 1;
		if (argv[i][0] == '-' && !toggle)
			i++;
		else
		{
			ft_bzero(&stat, sizeof(struct stat));
			lstat(argv[i], &stat);
			if (S_ISREG(stat.st_mode))
			{
				(*info).is_err = true;
				throw_err(argv[i], 1, info);
			}
			i++;
		}
	}
}

void	print_errors(char **argv, t_info *info, int i)
{
	if (i == -1)
		throw_err(argv[1], 0, info);
	else
	{
		print_nonfile(argv, info);
		print_reg(argv, info);
	}
	if ((*info).is_err && (*info).pc < (*info).dc)
	{
		ft_putendl("");
		(*info).is_err = false;
	}
}
