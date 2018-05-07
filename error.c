/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 20:19:20 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/06 20:44:03 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*throw_err(char *msg, int i, t_info *info, t_dir *list)
{
	char	path[1024];

	ft_bzero(path, 1024);
	(*info).pc++;
	if (i == -1)
	{
		(*info).dc--;
		ft_printf("ls: %s: No such file or directory\n", msg);
	}
	else if (i == 0)
	{
		while (*msg == '-' || ARGS(*msg) || *msg == 't')
			msg++;
		ft_printf(ILLEGAL, *msg);
	}
	else if (i == 1)
		ft_printf("%s\n", msg);
	else if (i == 2)
	{
		build_path(path, list);
		ft_printf("%s%s", PERM ? list->path : "", PERM ? ":\n" : "");
		ft_printf("ls: %s: Permission denied\n%s", msg, CPC);
	}
	return (NULL);
}

void	print_nonfile(char **argv, t_info *info)
{
	struct stat	stat;
	int			i;
	int			toggle;

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
				throw_err(argv[i], -1, info, NULL);
			i++;
		}
	}
}

void	print_reg(char **argv, t_info *info)
{
	struct stat	stat;
	int			i;
	int			toggle;

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
				throw_err(argv[i], 1, info, NULL);
			}
			i++;
		}
	}
}

int		check_params(char **argv, t_info *info)
{
	int i;
	int ret;

	i = 1;
	ret = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (i == 1 && DOUBLE && info->argc == 2)
			return (-1);
		else if (i == 1 && DOUBLE && info->argc != 2)
		{
			i++;
			continue;
		}
		if (argv[i][0] == '-' && (!argv[i][1] || argv[i][1] == '-'))
		{
			ret = 0;
			throw_err(argv[i], -1, info, NULL);
		}
		i++;
	}
	if (i == info->argc && !ret)
		exit(1);
	return (ret);
}

void	print_errors(char **argv, t_info *info, int *i)
{
	if (check_params(argv, info) == 0)
		*i = 1;
	else if ((check_params(argv, info)) == -1)
		*i = info->argc;
	if (*i == -1)
		throw_err(argv[1], 0, info, NULL);
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
