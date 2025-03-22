/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:36:15 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:44:42 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <math.h>

int	get_t2(t_ray *back_ray, t_vec3 *vhat, float *t, t_vec3 *poi)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	t_vec3	p;

	p = back_ray->point1;
	a = powf(vhat->x, 2) + powf(vhat->y, 2);
	b = 2.0 * (p.x * vhat->x + p.y * vhat->y);
	c = powf(p.x, 2) + powf(p.y, 2) - 1.0;
	delta = powf(b, 2) - (4.0 * a * c);
	if (delta > 0.0)
	{
		t[0] = (-b + sqrtf(delta)) / (2.0f * a);
		t[1] = (-b - sqrtf(delta)) / (2.0f * a);
		poi[0] = vec_add(back_ray->point1, scale_vector(*vhat, t[0]));
		poi[1] = vec_add(back_ray->point1, scale_vector(*vhat, t[1]));
		return (1);
	}
	return (0);
}

float	get_distance(t_ray *back_ray, t_vec3 *vhat, float *t, t_vec3 *poi)
{
	float	t2;

	t2 = get_t2(back_ray, vhat, t, poi);
	if (!t2)
		return (FLT_MAX);
	if (!(t[0] > 0.0 && fabs(poi[0].z) < 1.0))
		t[0] = 100e6;
	if (!(t[1] > 0.0 && fabs(poi[1].z) < 1.0))
		t[1] = 100e6;
	return (t2);
}

void	get_distance2(t_ray *back_ray, t_vec3 *vhat, float *t, t_vec3 *poi)
{
	float	t2;

	t2 = get_distance(back_ray, vhat, t, poi);
	if (t2 == FLT_MAX)
	{
		t[0] = 100e6;
		t[1] = 100e6;
	}
	if (fabs(vhat->z) < EPSILON)
	{
		t[2] = 100e6;
		t[3] = 100e6;
		return ;
	}
	t[2] = (back_ray->point1.z - 1) / -vhat->z;
	t[3] = (back_ray->point1.z + 1) / -vhat->z;
	poi[2] = vec_add(back_ray->point1, scale_vector(*vhat, t[2]));
	poi[3] = vec_add(back_ray->point1, scale_vector(*vhat, t[3]));
	if (!(t[2] > 0.0 && sqrtf(powf(poi[2].x, 2) + powf(poi[2].y, 2)) < 1.0))
		t[2] = 100e6;
	if (!(t[3] > 0.0 && sqrtf(powf(poi[3].x, 2) + powf(poi[3].y, 2)) < 1.0))
		t[3] = 100e6;
}

int	test_cylinder(t_ray *ray, t_info *info)
{
	t_cylinder_data	data;
	int				validint;

	data.back_ray = apply_transform(ray, info->e->gtfm, BACKWARD);
	data.vhat = normalize(data.back_ray.dir);
	data.min_index = 0;
	get_distance2(&data.back_ray, &data.vhat, data.t, data.poi);
	if (get_min(data.t, &data.min_index, 4) == FLT_MAX)
		return (0);
	validint = calculate_props(data.min_index, &data.poi[data.min_index], info,
			&data.vhat);
	if (validint && data.min_index >= 2)
	{
		if (dot_product(info->localn, ray->dir) > 0)
			info->localn = scale_vector(info->localn, -1);
	}
	return (validint);
}
