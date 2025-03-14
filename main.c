#include "main.h"
#include <stdio.h>
#include <stdlib.h>

// static int	handle_exit(t_vars *vars)
// {
// 	free_objects(vars);
// 	free_image(vars->image);
// 	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
// 	mlx_destroy_display(vars->mlx_ptr);
// 	exit(0);
// 	return (0);
// }

// static int	key_hook(int keycode, t_vars *vars)
// {
// 	if (keycode == 65307)
// 		handle_exit(vars);
// 	return (0);
// }

int test_intersection(t_object *list, t_info* info, t_ray *ray, int obj_count)
{
	float mindist = 1e6;
	float dist;
	int intfound = 0;
	int validint = 0;
	t_info	test;
	int i = 0;
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
				info->e = list + i; // current object
				info->hitpoint = test.hitpoint;
				info->localnormal = test.localnormal;
			}
		}
		i++;
	}
	return (intfound);
}


void raytrace(t_vars *vars)
{
	int x;
	int y;
	float xfact = 2.0f / (float)WIDTH;
	float yfact = 2.0f / (float)HEIGHT;
	t_vec3 color = (t_vec3) {0, 0, 0};
	y = 0;
	t_info info;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// convert x and y to [-1, 1]
			float normx = ((float)x * xfact) - 1.0;
			float normy = ((float)y * yfact) - 1.0;
			t_ray ray = generate_ray(normx, normy, &vars->cam);
			int intfound = test_intersection(vars->objects, &info, &ray, vars->obj_count);
			if (intfound)
			{
				printf("int found \n\n");

				color = diffuse_color(&info, vars, &info.e->base_color);
				color = vec_add(color , vars->ambient.color);
				// t_vec3 am = (t_vec3){vars->ambient.color.r, vars->ambient.color.g, vars->ambient.color.b};
				set_pixel(x, y, &color, vars->image);
			}
			x++;
		}
		y++;
	}
	printf("done\n");
}

// static int	loop(t_vars *vars)
// {
// 	raytrace(vars);
// 	render(vars->image, vars->mlx_ptr, vars->win_ptr);
// 	return (0);
// }

int main(int ac, char **av)
{
	t_vars vars;
	t_rt	*rt;

	if (ac != 2)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	rt = (t_rt *)malloc(sizeof(t_rt));
	if (rt == NULL)
	{
		perror("Failed to allocate memory for t_rt");
		exit(EXIT_FAILURE);
	}
	rt->object_count = 0;
	open_file(rt, av[1]);
	vars.obj_count = rt->object_count;
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr,
		WIDTH, HEIGHT, "miniRT");
	t_camera cam;
	cam.origin = rt->camera.position;
	cam.lookat = rt->camera.orientation;
	cam.fov = rt->camera.fov;
	setup_camera(&cam);
	vars.cam = cam;
	vars.ambient = rt->ambient;

	// printf("ambient red %f \n" , rt->ambient.color.r);
	// printf("ambient green %f \n" , rt->ambient.color.g);
	// printf("ambient blue %f \n" , rt->ambient.color.b);


	t_vec3 temp = (t_vec3){vars.ambient.color.x, vars.ambient.color.y, vars.ambient.color.z};
	temp = scale_vector(temp, vars.ambient.lighting);
	vars.ambient.color = (t_vec3){temp.x, temp.y, temp.z};
	vars.lights = malloc(sizeof(t_light));
	vars.lights->position = rt->light.position;
	vars.lights->brightness = rt->light.brightness;
	vars.lights->color = (t_vec3){1, 1, 1};
	list_object(&vars, rt);
	vars.image = new_image();
	raytrace(&vars);
	render(vars.image , vars.mlx_ptr , vars.win_ptr);
	mlx_loop(vars.mlx_ptr);
	// mlx_loop_hook(vars.mlx_ptr, loop , &vars);
	// mlx_loop(vars.mlx_ptr);
	return (0);
}
