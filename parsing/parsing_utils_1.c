/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:14:00 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/25 16:29:50 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	parse_ambient(t_rt *rt, char *line)
{
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (line_count(line_data) != 3 || rt->has_ambient)
		return (free_array_parse(line_data), arg_error("ambient"));
	if (check_between(line_data[1], 1, (int []){0, 1})
		&& check_between(line_data[2], 3, (int []){0, 255}))
	{
		set_ambient(line_data, &rt->ambient);
		rt->has_ambient = 1;
		free_array_parse(line_data);
		return (1);
	}
	free_array_parse(line_data);
	return (0);
}

int	parse_camera(t_rt *rt, char *line)
{
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (line_count(line_data) != 4 || rt->has_camera)
		return (free_array_parse(line_data), arg_error("camera"));
	if (check_range(line_data[1], 3)
		&& check_between(line_data[2], 3, (int []){-1, 1})
		&& check_between(line_data[3], 1, (int []){0, 180}))
	{
		set_camera(line_data, &rt->camera);
		rt->has_camera = 1;
		free_array_parse(line_data);
		return (1);
	}
	free_array_parse(line_data);
	return (0);
}

int	line_count(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	parse_light(t_rt *rt, char *line)
{
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (line_count(line_data) != 3 || rt->has_light) // adjust this before pushing
		return (free_array_parse(line_data), arg_error("light"));
	if (check_range(line_data[1], 3)
		&& check_between(line_data[2], 1, (int []){0, 1}))
	{
		set_light(line_data, &rt->light);
		rt->has_light = 1;
		free_array_parse(line_data);
		return (1);
	}
	free_array_parse(line_data);
	return (0);
}

int	valid_line(char *arg)
{
	if (!arg)
		return (0);
	if (!ft_strncmp(arg, "A", 0) || !ft_strncmp(arg, "C", 0)
		|| !ft_strncmp(arg, "L", 0) || !ft_strncmp(arg, "sp", 0)
		|| !ft_strncmp(arg, "pl", 0) || !ft_strncmp(arg, "cy", 0)
		|| !ft_strncmp(arg, "#", 1))
		return (1);
	return (0);
}
