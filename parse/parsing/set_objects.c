/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:31:31 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/18 13:32:25 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	set_cylinder(char **line, t_object_parse **list)
{
	t_cylinder		*cylinder;
	t_object_parse	*new_object;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return ;
	cylinder->diameter = atoi_double(line[3]);
	cylinder->height = atoi_double(line[4]);
	set_direction(line[1], &cylinder->position);
	set_direction(line[2], &cylinder->direction);
	set_rgb(line[5], &cylinder->color);
	new_object = (t_object_parse *)malloc(sizeof(t_object_parse));
	if (!new_object)
		return ;
	new_object->type = CYLINDER_PARSE;
	new_object->object = (void *)cylinder;
	new_object->color = cylinder->color;
	new_object->position = cylinder->position;
	new_object->next = NULL;
	ft_add_back(list, new_object, CYLINDER_PARSE);
}

void	set_plane(char **line, t_object_parse **list)
{
	t_plane			*plane;
	t_object_parse	*new_object;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return ;
	set_direction(line[1], &plane->position);
	set_direction(line[2], &plane->direction);
	set_rgb(line[3], &plane->color);
	new_object = (t_object_parse *)malloc(sizeof(t_object_parse));
	if (!new_object)
		return ;
	new_object->type = PLANE_PARSE;
	new_object->object = (void *)plane;
	new_object->color = plane->color;
	new_object->position = plane->position;
	new_object->next = NULL;
	ft_add_back(list, new_object, PLANE_PARSE);
}

void	set_sphere(char **line, t_object_parse **list)
{
	t_sphere		*sphere;
	t_object_parse	*new_object;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return ;
	sphere->diameter = atoi_double(line[2]);
	set_direction(line[1], &sphere->position);
	set_rgb(line[3], &sphere->color);
	new_object = (t_object_parse *)malloc(sizeof(t_object_parse));
	if (!new_object)
		return ;
	new_object->type = SPHERE_PARSE;
	new_object->object = (void *)sphere;
	new_object->color = sphere->color;
	new_object->position = sphere->position;
	new_object->next = NULL;
	ft_add_back(list, new_object, SPHERE_PARSE);
}

int	parse_obj(t_rt *rt, char *first_arg, char *line)
{
	if (!ft_strncmp(first_arg, "sp", ft_strlen("sp"))
		&& !parse_sphere(rt, line))
		return (0);
	if (!ft_strncmp(first_arg, "pl", ft_strlen("pl"))
		&& !parse_plane(rt, line))
		return (0);
	if (!ft_strncmp(first_arg, "cy", ft_strlen("cy"))
		&& !parse_cylinder(rt, line))
		return (0);
	return (1);
}
