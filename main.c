#include "main.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

static int	handle_exit(t_vars *vars)
{
	free_objects(vars);
	free_image(vars->image);
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
				color = diffuse_color(&info, vars, &info.e->base_color);
				t_vec3 ambient = (t_vec3) {0.12,0.084,0.048};
				color = vec_add(color, scale_vector(ambient, 0.1f));
				set_pixel(x, y, &color, vars->image);
			}
			x++;
		}
		y++;
	}
	printf("done\n");
}

int main(int ac, char **av)
{
	(void) ac;
	(void) av;
	t_vars vars;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr,
		WIDTH, HEIGHT, "miniRT");
	// init camera values
	vars.cam.origin = (t_vec3) {2, -20, -5};
	vars.cam.lookat = (t_vec3) {0, 0, 0};
	vars.cam.fov = 40;
	setup_camera(&vars.cam);
	vars.image = new_image();
	vars.obj_count = 4;
	list_object(&vars);
	vars.lights = malloc(sizeof(t_light));
	vars.lights[0].brightness = 1;
	vars.lights[0].color = (t_vec3) {1, 1, 1};
	vars.lights[0].position = (t_vec3) {0, -20, -5};
	raytrace(&vars);
	render(vars.image, vars.mlx_ptr, vars.win_ptr);
	mlx_hook(vars.win_ptr, 2, 1L << 0, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, handle_exit, &vars);
	mlx_loop(vars.mlx_ptr);
}