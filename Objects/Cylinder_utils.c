/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:42:21 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:45:30 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	handle_caps(t_info *info, t_vec3 *poi)
{
	info->hitpoint = apply_transform_vector(*poi, FORWARD, info->e->gtfm);
	info->localn = info->e->d_normal;
}

int	calculate_props(int min_index, t_vec3 *poi, t_info *info, t_vec3 *vhat)
{
	if (min_index < 2)
	{
		info->hitpoint = apply_transform_vector(*poi, FORWARD, info->e->gtfm);
		info->localn = normalize(vec_sub(info->hitpoint, info->e->translation));
		return (1);
	}
	else
	{
		if (fabs(vhat->z) < EPSILON)
			return (0);
		if (sqrtf(powf(poi->x, 2) + powf(poi->y, 2)) < 1.0)
		{
			handle_caps(info, poi);
			return (1);
		}
		return (0);
	}
	return (0);
}

// [t0, t1, t2, t3]
// [0, 1, 2, 3]
float	get_min(float *t, int *min_index, int size)
{
	float	min;
	int		i;

	i = 0;
	if (size == 4 && t[0] == 100e6 && t[1] == 100e6 && t[2] == 100e6
		&& t[3] == 100e6)
		return (FLT_MAX);
	if (size == 3 && t[0] == 100e6 && t[1] == 100e6 && t[2] == 100e6)
		return (FLT_MAX);
	min = 10e6;
	while (i < size)
	{
		if (t[i] < min)
		{
			min = t[i];
			*min_index = i;
		}
		i++;
	}
	return (min);
}
