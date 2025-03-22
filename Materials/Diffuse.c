/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:50:54 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:58:06 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	cast_ray(t_ray *lightray, t_vars *vars, float lighdist,
		t_info *info)
{
	int		i;
	int		validint;
	float	dist;
	t_info	test;

	i = 0;
	validint = 0;
	while (i < vars->obj_count)
	{
		if (info->e != &vars->objects[i])
		{
			test.e = &vars->objects[i];
			validint = vars->objects[i].intersect(lightray, &test);
			if (validint)
			{
				dist = length(vec_sub(test.hitpoint, info->hitpoint));
				if (dist > lighdist)
					validint = 0;
			}
			if (validint)
				break ;
		}
		i++;
	}
	return (validint);
}

int	compute_illimunation(t_light *light, t_info *info, t_vars *vars,
		float *intensity)
{
	t_vec3	lighdir;
	t_ray	lightray;
	float	lighdist;
	int		validint;

	lighdir = normalize(vec_sub(light->position, info->hitpoint));
	lighdist = length(vec_sub(light->position, info->hitpoint));
	lightray = new_ray(info->hitpoint, vec_add(info->hitpoint, lighdir));
	validint = cast_ray(&lightray, vars, lighdist, info);
	if (!validint)
	{
		*intensity = light->brightness * fmax(dot_product(lighdir,
					info->localn), 0.0);
		return (1);
	}
	else
	{
		*intensity = 0.0f;
		return (0);
	}
	return (0);
}

static void	process_light(t_diffuse_data *data, t_light *light,
	t_info *info, t_vars *vars)
{
	int	validillum;

	validillum = compute_illimunation(light, info, vars, &data->intensity);
	if (validillum)
	{
		data->illumfound = 1;
		data->color.x = light->color.x * data->intensity;
		data->color.y = light->color.y * data->intensity;
		data->color.z = light->color.z * data->intensity;
	}
}

t_vec3	diffuse_color(t_info *info, t_vars *vars, t_vec3 *base_color)
{
	t_diffuse_data	data;

	data.intensity = 0;
	data.diffuse = (t_vec3){0, 0, 0};
	data.color = (t_vec3){0, 0, 0};
	data.illumfound = 0;
	process_light(&data, &vars->lights[0], info, vars);
	if (data.illumfound)
	{
		data.diffuse = (t_vec3){
			data.color.x * base_color->x,
			data.color.y * base_color->y,
			data.color.z * base_color->z
		};
	}
	return (data.diffuse);
}
