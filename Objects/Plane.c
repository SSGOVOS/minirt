/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:45:11 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:45:13 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	test_plane(t_ray *ray, t_info *info)
{
	t_vec3	axis;
	t_vec3	vhat;
	t_vec3	origin;
	float	denom;
	float	t;

	origin = info->e->translation;
	vhat = ray->dir;
	axis = info->e->d_normal;
	denom = dot_product(axis, vhat);
	if (fabs(denom) < EPSILON)
		return (0);
	t = (dot_product(origin, axis) - dot_product(ray->point1, axis)) / denom;
	if (t < EPSILON)
		return (0);
	info->localn = axis;
	if (dot_product(info->localn, vhat) > 0)
		info->localn = scale_vector(info->localn, -1);
	info->hitpoint = vec_add(ray->point1, scale_vector(vhat, t));
	return (1);
}
