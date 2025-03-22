/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:45:06 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:48:26 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

float	get_dist(t_vec3 ray_org, t_vec3 vhat) // vhat is the ray dir normalized
{
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;

	b = 2.0 * dot_product(ray_org, vhat);
	c = dot_product(ray_org, ray_org) - 1.0f;
	delta = pow(b, 2) - (4.0 * c);
	if (delta > 0)
	{
		delta = sqrtf(delta);
		t1 = (-b - delta) / 2.0;
		t2 = (-b + delta) / 2.0;
		if (t1 < 0.0 || t2 < 0.0)
			return (FLT_MAX);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	return (FLT_MAX);
}

int	test_sphere(t_ray *ray, struct s_info *info)
{
	t_ray	backray;
	t_vec3	vhat;
	float	t;
	t_vec3	localint;

	backray = apply_transform(ray, info->e->gtfm, BACKWARD);
	vhat = backray.dir;
	t = get_dist(backray.point1, vhat);
	if (t == FLT_MAX)
		return (0);
	localint = vec_add(backray.point1, scale_vector(vhat, t));
	info->hitpoint = apply_transform_vector(localint, FORWARD, info->e->gtfm);
	info->localn = normalize(vec_sub(info->hitpoint, info->e->translation));
	return (1);
}
