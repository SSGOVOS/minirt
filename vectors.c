/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:31:39 by amoubine          #+#    #+#             */
/*   Updated: 2025/02/28 18:58:57 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// cos of the angle between the 2 vectors, they have to be normalized
float	dot_product(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

// the third vector that is third vector that is perpendicular (3amodi) on the 2 vectors
t_vec3	cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

float	length2(t_vec3 a)
{
	return (pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

float	length(t_vec3 a)
{
	return (sqrtf(length2(a)));
}

// scale vector by a variable
t_vec3	scale_vector(t_vec3 vec, float t)
{
	return ((t_vec3){vec.x * t, vec.y * t, vec.z * t});
}

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
