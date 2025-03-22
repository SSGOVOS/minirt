/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:31:39 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:32:16 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// cos of the angle between the 2 vectors, they have to be normalized
float	dot_product(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

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
