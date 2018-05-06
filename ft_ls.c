/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrommen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:16:02 by ckrommen          #+#    #+#             */
/*   Updated: 2018/05/05 18:59:17 by ckrommen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*create_sub(t_dir **list, char *name)
{
	t_dir *ptr;

	ptr = *list;
	while (ptr && ft_strcmp(ptr->d_info->d_name, name) != 0)
		ptr = ptr->next;
	return (ptr);
}

t_dir		*ft_ls(t_info *info, t_dir **list)
{
	struct dirent	*file;
	struct stat		buf;
	DIR				*fd;

	file = NULL;
	lstat(info->dir_name, &buf);
	if (!(fd = opendir(info->dir_name)) && !S_ISREG(buf.st_mode) && info->re)
		return (throw_err(info->dir_name, 2, info));
	while ((file = readdir(fd)) != NULL)
	{
		if ((!info->a && !ft_strncmp(file->d_name, ".", 1)))
			continue ;
		add_dir(list, info->dir_name, file->d_name, buf, file);
		ft_strcat(info->dir_name, "/");
		ft_strcat(info->dir_name, file->d_name);
		ft_bzero(&buf, sizeof(struct stat));
		lstat(info->dir_name, &buf);
		if (info->re && S_ISDIR(buf.st_mode) != 0 && ft_strncmp(".", file->d_name, 1) != 0)
			ft_ls(info, &(create_sub(list, file->d_name)->sub_dir));
		rm_dir(info);
	}
	closedir(fd);
	*list = merge_sort(*list);
	return (*list);
}

int main(int argc, char **argv)
{
	t_dir			*list;
	t_info	info;
	bool		i;

	list = NULL;
	info = init_info(argc, count_dir(argv));
	i = load_flags(&info, argv);			
	print_errors(argv, &info, i);
	if (i == argc)
	{
		ft_strcpy(info.dir_name, ".");
		if ((list = ft_ls(&info, &list)) != NULL)
			info.r ? rev_print_list(list, &info) : print_list(list, &info);
	}
	while (argv[i])
	{
		if (check_arg(argv[i]))
		{
			ft_strcpy(info.dir_name, argv[i]);
			if ((list = ft_ls(&info, &list)) != NULL)
				info.r ? rev_print_list(list, &info) : print_list(list, &info);
//			print_perm()
			list = NULL; // NEED TO FREE THIS FUCKING GARGANTUAN LIST AT SOME POINT (-_-)
			
		}
		i++;
	}
	return (1);
}
