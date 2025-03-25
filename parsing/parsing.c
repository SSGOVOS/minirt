/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:18:56 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/25 17:29:39 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	check_range(char *line, int count)
{
	int		i;
	char	**line_arr;

	i = 0;
	line_arr = ft_split(line, ',');
	if (!line_arr)
		return (0);
	while (i < count)
	{
		if (!line_arr[i] || !is_float(line_arr[i]))
			return (free_array_parse(line_arr), 0);
		i++;
	}
	free_array_parse(line_arr);
	return (1);
}

int	check_between(char *line, int count, const int range[2])
{
	int		i;
	char	**line_arr;

	i = 0;
	if (!line)
		return (0);
	line_arr = ft_split(line, ',');
	if (!line_arr)
		return (0);
	while (i < count)
	{
		if (!line_arr[i] || !is_float(line_arr[i])
			|| (atoi_double(line_arr[i]) < range[0]
				|| atoi_double(line_arr[i]) > range[1]))
			return (free_array_parse(line_arr), 0);
		i++;
	}
	free_array_parse(line_arr);
	return (1);
}

static int	process_line(t_rt *rt, char *line)
{
	char	*first_arg;
	char	*sp;

	if (line[0] == '\n' || line[0] == '\0')
		return (free(line), 0);
	sp = ft_strchr(line, ' ');
	if (sp)
		first_arg = ft_substr(line, 0, sp - line);
	else
		first_arg = ft_strdup(line);
	if (!first_arg || !valid_line(first_arg))
		return (free(line), free(first_arg), parsing_error("INVALID LINE"), 1);
	if (!ft_strncmp(first_arg, "A", ft_strlen("A"))
		&& !parse_ambient(rt, line))
		return (free(line), free(first_arg), parsing_error("AMBIENT"), 1);
	if (!ft_strncmp(first_arg, "C", ft_strlen("C"))
		&& !parse_camera(rt, line))
		return (free(line), free(first_arg), parsing_error("CAMERA"), 1);
	if (!ft_strncmp(first_arg, "L", ft_strlen("L"))
		&& !parse_light(rt, line))
		return (free(line), free(first_arg), parsing_error("LIGHT"), 1);
	if (!parse_obj(rt, first_arg, line))
		return (free(line), free(first_arg), parsing_error("OBJECT"), 1);
	return (free(first_arg), free(line), 0);
}

int	parse(t_rt *rt)
{
	char	*line;

	rt->object = NULL;
	line = get_next_line(rt->file_fd);
	while (line != NULL)
	{
		for (int i = 0; line[i]; i ++)
		{
			if (line[i] == '\n')
				line[i] = '\0';
		}
		if (process_line(rt, line))
			return (1);
		line = get_next_line(rt->file_fd);
	}
	return (0);
}
