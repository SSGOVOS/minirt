#include "../main.h"

float	get_dist(t_vec3 ray_org, t_vec3 vhat) // vhat is the ray dir normalized
{
	float	b;
	float	c;
	float	delta;
	float	t1;
	float	t2;

	// these calculations are based on sphere pos is 0,0,0 and radius is 1
	b = 2.0 * dot_product(ray_org, vhat);
	c = dot_product(ray_org, ray_org) - 1.0f;
	delta = pow(b, 2) - (4.0 * c);
	if (delta > 0)
	{
		delta = sqrtf(delta);
		t1 = (-b - delta) / 2.0;
		t2 = (-b + delta) / 2.0;
		if (t1 < 0.0 || t2 < 0.0)
			return (FLT_MAX);
		if (t1 < t2)
			return (t1);
		return (t2);
	}
	return (FLT_MAX);
}

int test_sphere(t_ray * ray,  struct s_info *info)
{
	t_ray backray = apply_transform(ray, info->e->gtfm, BACKWARD);
	t_vec3 vhat = backray.dir;
	float t = get_dist(backray.point1, vhat);
	if (t == FLT_MAX)
		return (0);
	// int point = ray = origin + dir * t (t is found now)
	t_vec3 localint = vec_add(backray.point1, scale_vector(vhat, t));
	info->hitpoint = apply_transform_vector(localint, FORWARD, info->e->gtfm);
	// transform the inpoint to world coordinates
	info->localnormal = normalize(vec_sub(info->hitpoint, info->e->translation));
	// normal of sphere is normalized(hitpoint - sphere origin)
	// for sphere at 0.0.0 just normalized(hitpoint)
	return 1;
}
