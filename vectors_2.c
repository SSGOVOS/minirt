/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:29:56 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:30:16 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// make a unit vector
t_vec3	normalize(t_vec3 vec)
{
	float	l;
	t_vec3	new;

	l = length(vec);
	new = vec;
	if (l != 0)
		new = scale_vector(vec, 1.0f / l);
	return (new);
}

void	print_vector(t_vec3 a)
{
	printf("%f %f %f\n", a.x, a.y, a.z);
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

// get rotation vector of a normal, converting the normal to 0,0,-1 always
t_vec3	get_rotation_vector(t_vec3 normal)
{
	float	x;
	float	y;
	float	z;

	x = atan2(normal.y, -normal.z);
	y = atan2(-normal.x, sqrtf(powf(normal.y, 2) + powf(normal.z, 2)));
	z = atan2(normal.x, normal.y);
	return ((t_vec3){x, y, z});
}
