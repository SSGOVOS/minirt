#include "../main.h"

static int	cast_ray(t_object *objects, t_ray cast_ray, int count)
{
	t_info	test;
	int		i;
	int		validint;

	i = 0;
	while (i < count)
	{
		test.e = &objects[i];
		validint = objects[i].intersect(&cast_ray, &test);
		if (validint)
			return (1);
		i++;
	}
	return (0);
}


float	get_intensity(t_vec3 light_ray_dir, t_vec3 normal,
	t_vec3 cam_dir)
{
	t_vec3	v;
	t_vec3	ref_v;
	float	prod;

	v = normalize(cam_dir);
	ref_v = reflect(normalize(light_ray_dir), normal);
	prod = dot_product(ref_v, v);
	if (prod > 0.0)
		return (0.35 * powf(prod, 20));
	return (0);
}

t_vec3	specular_highlight(t_vars *vars, t_info *info, t_ray *camera_ray)
{
	t_vec3 color = (t_vec3) {0, 0, 0};
	float intensity = 0.0f;
	int	i;
	
	t_vec3 lightdir;
	t_vec3 start;
	t_vec3 point2;
	t_ray lightray;
	int validint = 0;
	i = 0;
	// replace 1 with light count
	while (i < 1)
	{
		lightdir = normalize(
				vec_sub(vars->lights[i].position, info->hitpoint));
		start = vec_add(info->hitpoint,
				scale_vector(lightdir, 0.0001f));
		point2 = vec_add(start, lightdir);
		lightray = new_ray(start, point2);
		validint = cast_ray(vars->objects,
				lightray, vars->obj_count);
		if (!validint)
			intensity = get_intensity(lightray.dir,
					info->localnormal, camera_ray->dir);
		color.x += vars->lights[i].color.x * intensity
			* vars->lights[i].brightness;
		color.y += vars->lights[i].color.y * intensity
			* vars->lights[i].brightness;
		color.z += vars->lights[i].color.z * intensity
			* vars->lights[i].brightness;
		i++;
	}
	return (color);
}