#include "main.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>



int test_intersection(t_object *list, t_info* info, t_ray *ray)
{
	float mindist = 1e6;
	float dist;
	int intfound = 0;
	int validint = 0;
	t_info	test;
	t_object *head = list;
	while (head)
	{
		test.e = head;
		validint = head->intersect(ray, &test);
		if (validint)
		{
			intfound = 1;
			dist = length(vec_sub(test.hitpoint, ray->point1));
			if (dist < mindist)
			{
				mindist = dist;
				info->e = head; // current object
				info->hitpoint = test.hitpoint;
				info->localnormal = test.localnormal;
			}
		}
		head = head->next;
	}
	return (intfound);
}


void raytrace(t_object *list, t_vars *vars)
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
			int intfound = test_intersection(list, &info, &ray);
			if (intfound)
			{
				color = info.e->base_color;
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
	vars.cam.origin = (t_vec3) {1, -7, 0.5};
	vars.cam.lookat = (t_vec3) {0, 0, 0};
	vars.cam.fov = 60;
	setup_camera(&vars.cam);
	vars.image = new_image();
	t_object *list = list_object();
	raytrace(list, &vars);
	render(vars.image, vars.mlx_ptr, vars.win_ptr);
	mlx_loop(vars.mlx_ptr);
}