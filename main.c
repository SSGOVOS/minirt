/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:37:00 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 06:37:28 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	handle_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		handle_exit(vars);
	return (0);
}

int	test_intersection(t_object *list, t_info *info, t_ray *ray, int obj_count)
{
	float	mindist;
	float	dist;
	int		intfound;
	int		validint;
	t_info	test;
	int		i;

	intfound = 0;
	validint = 0;
	mindist = 1e6;
	i = 0;
	while (i < obj_count)
	{
		test.e = list + i;
		validint = list[i].intersect(ray, &test);
		if (validint)
		{
			intfound = 1;
			dist = length(vec_sub(test.hitpoint, ray->point1));
			if (dist < mindist)
			{
				mindist = dist;
				info->e = list + i;
				info->hitpoint = test.hitpoint;
				info->localnormal = test.localnormal;
			}
		}
		i++;
	}
	return (intfound);
}

void	raytrace(t_vars *vars)
{
	int		x;
	int		y;
	float	xfact;
	float	yfact;
	t_vec3	color;
	t_info	info;
	float	normx;
	float	normy;
	t_ray	ray;
	int		intfound;

	xfact = 2.0f / (float)WIDTH;
	yfact = 2.0f / (float)HEIGHT;
	color = (t_vec3){0, 0, 0};
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			normx = ((float)x * xfact) - 1.0;
			normy = ((float)y * yfact) - 1.0;
			ray = generate_ray(normx, normy, &vars->cam);
			intfound = test_intersection(vars->objects, &info, &ray,
					vars->obj_count);
			if (intfound)
			{
				color = diffuse_color(&info, vars, &info.e->base_color);
				color = vec_add(color, vars->ambient.color);
				set_pixel(x, y, &color, vars->image);
			}
			x++;
		}
		y++;
	}
}

t_rt	*initialize_rt(char *filename)
{
	t_rt	*rt;

	rt = (t_rt *)malloc(sizeof(t_rt));
	if (rt == NULL)
	{
		perror("Failed to allocate memory for t_rt");
		exit(EXIT_FAILURE);
	}
	rt->object_count = 0;
	open_file(rt, filename);
	return (rt);
}

t_vars	initialize_vars(t_rt *rt)
{
	t_vars		vars;
	t_camera	cam;
	t_vec3		temp;

	vars.obj_count = rt->object_count;
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "miniRT");
	vars.file_fd = rt->file_fd;
	cam.origin = rt->camera.position;
	cam.lookat = rt->camera.orientation;
	cam.fov = rt->camera.fov;
	setup_camera(&cam);
	vars.cam = cam;
	vars.ambient = rt->ambient;
	temp = (t_vec3){vars.ambient.color.x, vars.ambient.color.y,
		vars.ambient.color.z};
	temp = scale_vector(temp, vars.ambient.lighting);
	vars.ambient.color = (t_vec3){temp.x, temp.y, temp.z};
	vars.lights = malloc(sizeof(t_light));
	vars.lights->position = rt->light.position;
	vars.lights->brightness = rt->light.brightness;
	vars.lights->color = (t_vec3){1, 1, 1};
	list_object(&vars, rt);
	vars.image = new_image();
	return (vars);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	t_rt	*rt;

	if (ac != 2)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	rt = initialize_rt(av[1]);
	vars = initialize_vars(rt);
	raytrace(&vars);
	render(vars.image, vars.mlx_ptr, vars.win_ptr);
	mlx_hook(vars.win_ptr, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, handle_exit, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
