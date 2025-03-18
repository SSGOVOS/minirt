/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:19:05 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/18 13:19:31 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	set_direction(char *line, t_vec3 *directions)
{
	char	**xyz;

	xyz = ft_split(line, ',');
	directions->x = atoi_double(xyz[0]);
	directions->y = atoi_double(xyz[1]);
	directions->z = atoi_double(xyz[2]);
	free_array_parse(xyz);
}

void	set_rgb(char *line, t_vec3 *colors)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	colors->x = (float)ft_atoi(rgb[0]) / 255.0f;
	colors->y = (float)ft_atoi(rgb[1]) / 255.0f;
	colors->z = (float)ft_atoi(rgb[2]) / 255.0f;
	free_array_parse(rgb);
}

void	set_camera(char **line, t_camera_parse *camera)
{
	camera->fov = ft_atoi(line[3]);
	set_direction(line[1], &camera->position);
	set_direction(line[2], &camera->orientation);
}

void	set_light(char **line, t_light *light)
{
	set_direction(line[1], &light->position);
	light->brightness = atoi_double(line[2]);
}

void	set_ambient(char **line, t_ambient *ambient)
{
	ambient->lighting = atoi_double(line[1]);
	set_rgb(line[2], &ambient->color);
}
