/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:24:50 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:28:10 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	prepare_cylinder(t_object *list)
{
	list->d_normal = normalize(list->d_normal);
	list->rotation = get_rotation_vector(list->d_normal);
	list->scale = (t_vec3){list->radius, list->radius, list->height};
	list->gtfm = set_transform(&list->translation, &list->rotation,
			&list->scale);
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
			prepare_cylinder(list + i);
		}
		i++;
	}
}
