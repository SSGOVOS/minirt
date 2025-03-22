/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:23:04 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/20 08:05:12 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void prepare_cylinder(t_object *list)
{
	list->d_normal = normalize(list->d_normal);
	list->rotation = get_rotation_vector(list->d_normal);
	list->scale = (t_vec3){list->radius, list->radius,
		list->height};
	list->gtfm = set_transform(&list->translation,
			&list->rotation, &list->scale);
	list->intersect = test_cylinder;
}
void	prepare_objects(t_object *list, int obj_count)
{
	int	i;

	i = 0;
	while (i < obj_count)
	{
		if (list[i].type == SPHERE)
		{
			list[i].rotation = (t_vec3){0, 0, 0};
			list[i].scale = (t_vec3){list[i].radius, list[i].radius,
				list[i].radius};
			list[i].gtfm = set_transform(&list[i].translation,
					&list[i].rotation, &list[i].scale);
			list[i].intersect = test_sphere;
		}
		else if (list[i].type == PLANE)
		{
			list[i].d_normal = normalize(list[i].d_normal);
			list[i].intersect = test_plane;
		}
		else if (list[i].type == CYLINDER)
		{
			prepare_cylinder(list+i);
		}
		i++;
	}
}

// parse to get this
static void	init_sphere(t_object *object, t_sphere *sphere)
{
	object->type = SPHERE;
	object->translation = sphere->position;
	object->base_color = sphere->color;
	object->radius = (float)(sphere->diameter) / 2.0f;
}

static void	init_plane(t_object *object, t_plane *plane)
{
	object->type = PLANE;
	object->translation = plane->position;
	object->base_color = plane->color;
	object->d_normal = plane->direction;
}

static void	init_cylinder(t_object *object, t_cylinder *cylinder)
{
	object->type = CYLINDER;
	object->translation = cylinder->position;
	object->base_color = cylinder->color;
	object->radius = (float)(cylinder->diameter) / 2.0f;
	object->height = cylinder->height;
	object->d_normal = cylinder->direction;
}

void	list_object(t_vars *vars, t_rt *rt)
{
	int				i;
	t_object_parse	*head;

	vars->objects = malloc(sizeof(t_object) * vars->obj_count);
	head = rt->object;
	i = 0;
	while (head)
	{
		if (head->type == SPHERE_PARSE)
			init_sphere(&vars->objects[i], (t_sphere *)(head->object));
		else if (head->type == PLANE_PARSE)
			init_plane(&vars->objects[i], (t_plane *)(head->object));
		else if (head->type == CYLINDER_PARSE)
			init_cylinder(&vars->objects[i], (t_cylinder *)(head->object));
		i++;
		head = head->next;
	}
	prepare_objects(vars->objects, vars->obj_count);
}
