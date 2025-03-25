/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:37:00 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/25 14:21:33 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	handle_exit(t_vars *vars)
{
	free_objects(vars);
	free_image(vars->image);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->lights);
	free(vars->mlx_ptr);
	free_objects_parse(vars->rt->object);
	close(vars->rt->file_fd);
	free(vars->rt);
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		handle_exit(vars);
	return (0);
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
	vars.rt = rt;
	raytrace(&vars);
	render(vars.image, vars.mlx_ptr, vars.win_ptr);
	mlx_hook(vars.win_ptr, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, handle_exit, &vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
