/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:59:01 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/23 22:31:38 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	open_file(t_rt *rt, char *path)
{
	rt->object = NULL;
	rt->file_fd = open(path, O_RDONLY);
	rt->file = path;
	if (check_file(rt) == 1 || parse(rt) == 1)
	{
		close(rt->file_fd);
		if (rt->object)
			free_objects_parse(rt->object);
		if (rt->file_fd > 0)
			close(rt->file_fd);
		free(rt);
		exit(1);
	}
}

int	check_file(t_rt *rt)
{
	if (rt->file == NULL)
	{
		printf("Error: file is NULL\n");
		return (1);
	}
	if (rt->file_fd < 0)
	{
		printf("Error: file descriptor is invalid\n");
		return (1);
	}
	if (is_rt_file(rt->file) == 0)
	{
		printf("Error: file is not a .rt file\n");
		return (1);
	}
	return (0);
}

int	is_rt_file(char *path)
{
	int	len;

	len = (int)ft_strlen(path) - 3;
	if (len > 3)
		return (ft_strncmp(path + len, ".rt", 3) == 0);
	return (0);
}
