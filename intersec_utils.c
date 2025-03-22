/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:17:08 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:45:47 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	check_intersection(t_object *obj, t_intersect_data *data)
{
	int		validint;
	float	dist;

	validint = obj->intersect(data->ray, data->test);
	if (validint)
	{
		dist = length(vec_sub(data->test->hitpoint, data->ray->point1));
		if (dist < *(data->mindist))
		{
			*(data->mindist) = dist;
			data->info->e = obj;
			data->info->hitpoint = data->test->hitpoint;
			data->info->localn = data->test->localn;
		}
		return (1);
	}
	return (0);
}

int	test_intersection(t_object *list, t_info *info, t_ray *ray, int obj_count)
{
	float				mindist;
	int					intfound;
	t_info				test;
	t_intersect_data	data;
	int					i;

	intfound = 0;
	mindist = 1e6;
	i = 0;
	data.test = &test;
	data.info = info;
	data.ray = ray;
	data.mindist = &mindist;
	while (i < obj_count)
	{
		test.e = list + i;
		if (check_intersection(&list[i], &data))
			intfound = 1;
		i++;
	}
	return (intfound);
}

static void	process_pixel(int x, int y, t_ray_data *data, t_vars *vars)
{
	float	normx;
	float	normy;
	int		intfound;

	normx = ((float)x * data->xfact) - 1.0;
	normy = ((float)y * data->yfact) - 1.0;
	data->ray = generate_ray(normx, normy, &vars->cam);
	intfound = test_intersection(vars->objects, &data->info, &data->ray,
			vars->obj_count);
	if (intfound)
	{
		data->color = diffuse_color(&data->info, vars,
				&data->info.e->base_color);
		data->color = vec_add(data->color, vars->ambient.color);
		set_pixel(x, y, &data->color, vars->image);
	}
}

void	raytrace(t_vars *vars)
{
	int			x;
	int			y;
	t_ray_data	data;

	data.xfact = 2.0f / (float)WIDTH;
	data.yfact = 2.0f / (float)HEIGHT;
	data.color = (t_vec3){0, 0, 0};
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			process_pixel(x, y, &data, vars);
			x++;
		}
		y++;
	}
}
