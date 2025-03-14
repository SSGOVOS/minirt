#include "../main.h"


static int	cast_ray(t_ray *lightray, t_vars *vars,
		float lighdist, t_info *info)
{
	int		i;
	int		validint;
	float	dist;
	t_info	test;

	i = 0;
	validint = 0;
	while (i < vars->obj_count)
	{
		// skip current tested object, dont test intersection with itself because it will be true
		if (info->e != &vars->objects[i])
		{
			printf("object found in cast_ray\n");
			test.e = &vars->objects[i];
			validint = vars->objects[i].intersect(lightray, &test);
			if (validint)
			{
				dist = length(vec_sub(test.hitpoint, info->hitpoint));
				// test if the distance is bigger than the light dist
				// meaning the object we intersected with is either behind the light or between them
				if (dist > lighdist)
					validint = 0;
			}
			// break in case of intersection, one is enough to determine there is a shadow
			if (validint)
				break ;
		}
		i++;
	}
	return (validint);
}

int	compute_illimunation(t_light *light, t_info *info,
		t_vars *vars, float *intensity)
{
	t_vec3	lighdir;
	t_ray	lightray;
	float	lighdist;
	int		validint;

	// make a normal vector pointing the direction from intpoint to the light 
	lighdir = normalize(vec_sub(light->position, info->hitpoint));
	// calculate distance so we dont render objects behind the light
	lighdist = length(vec_sub(light->position, info->hitpoint));
	// make ray (intpoint, direction to light)
	lightray = new_ray(info->hitpoint, vec_add(info->hitpoint, lighdir));
	// test intersection of all objects in the scene
	validint = cast_ray(&lightray, vars, lighdist, info);
	if (!validint)
	{
		// calculate intensity based on angle between normal and light direction
		*intensity = light->brightness * fmax(dot_product(lighdir, info->localnormal), 0.0);
		return (1);
	}
	else
	{
		// means there was an object blocking the light on that point of the object
		*intensity = 0.0f;
		return (0);
	}
	return (0);
}

t_vec3	diffuse_color(t_info *info, t_vars *vars, t_vec3 *base_color)
{

	int illumfound = 0;
	t_vec3 color =  (t_vec3) {0, 0, 0};
	t_vec3 diffuse =  (t_vec3) {0, 0, 0};
	float intensity = 0;
	int validillum = 0;
	int	i;

	i = 0;
	// for bonus replace 1 with light count
	validillum = compute_illimunation(&vars->lights[i],
			info, vars, &intensity);
	if (validillum)
	{
		printf("valid int found\n");
		illumfound = 1;
		color.x = vars->lights[i].color.r * intensity;
		color.y = vars->lights[i].color.g * intensity;
		color.z = vars->lights[i].color.b * intensity;
	}
	if (illumfound)
	{
		diffuse = (t_vec3) {color.x * base_color->x,
							color.y * base_color->y,
							color.z * base_color->z};
	}
	return (diffuse);
}
