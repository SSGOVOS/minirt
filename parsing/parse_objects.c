/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:25:45 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/25 17:28:19 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	parsing_error(char *message)
{
	if (message)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(message, 2);
	}
}

int	parse_cylinder(t_rt *rt, char *line)
{
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (line_count(line_data) != 6)
		return (free_array_parse(line_data), arg_error("cylinder"));
	if (check_range(line_data[1], 3)
		&& check_between(line_data[2], 3, (int []){-1, 1})
		&& check_between(line_data[3], 1, (int []){-1, INT_MAX})
		&& check_between(line_data[4], 1, (int []){0, INT_MAX})
		&& check_between(line_data[5], 3, (int []){0, 255}))
	{
		set_cylinder(line_data, &rt->object);
		free_array_parse(line_data);
		rt->object_count++;
		return (1);
	}
	free_array_parse(line_data);
	return (0);
}

int	parse_plane(t_rt *rt, char *line)
{
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (line_count(line_data) != 4)
		return (free_array_parse(line_data), arg_error("plane"));
	if (check_range(line_data[1], 3)
		&& check_between(line_data[2], 3, (int []){-1, 1})
		&& check_between(line_data[3], 3, (int []){0, 255}))
	{
		set_plane(line_data, &rt->object);
		free_array_parse(line_data);
		rt->object_count++;
		return (1);
	}
	free_array_parse(line_data);
	return (0);
}

int	parse_sphere(t_rt *rt, char *line)
{
	char	**line_data;

	line_data = ft_split(line, ' ');
	if (line_count(line_data) != 4)
		return (free_array_parse(line_data), arg_error("sphere"));
	if (check_range(line_data[1], 3)
		&& check_between(line_data[2], 1, (int []){0, INT_MAX})
		&& check_between(line_data[3], 3, (int []){0, 255}))
	{
		set_sphere(line_data, &rt->object);
		free_array_parse(line_data);
		rt->object_count++;
		return (1);
	}
	free_array_parse(line_data);
	return (0);
}
