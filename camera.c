#include "main.h"


void setup_camera(t_camera *cam)
{
	t_vec3	upvec = (t_vec3) {0, 0, 1}; //arbitrary starting point to calculate u v of the camera
	cam->aspect_ratio = (float) WIDTH / (float) HEIGHT;
	float rad_fov = cam->fov * M_PI / 180;
	int focal_length = 1;
	cam->horizontal_size = 2.0 * focal_length * tanf(rad_fov / 2.0);
	cam->camera_w = normalize(vec_sub(cam->lookat, cam->origin));
	cam->camera_u = normalize(cross_product(cam->camera_w, upvec));
	cam->camera_v = normalize(cross_product(cam->camera_u, cam->camera_w));
	cam->screen_center = vec_add(cam->origin , scale_vector(cam->camera_w , focal_length));
	cam->screen_u = scale_vector(cam->camera_u, cam->horizontal_size);
	cam->screen_v = scale_vector(cam->camera_v, cam->horizontal_size / cam->aspect_ratio);
}

t_ray new_ray(t_vec3 point1, t_vec3 point2)
{
	t_ray ray;
	ray.point1 = point1;
	ray.point2 = point2;
	ray.dir = normalize(vec_sub(point2, point1));
	return (ray);
}

t_ray generate_ray(float x, float y, t_camera *cam)
{
	t_vec3 part1 = vec_add(cam->screen_center, scale_vector(cam->screen_u, x));
	t_vec3 part2 = vec_add(part1, scale_vector(cam->screen_v, y));
	return new_ray(cam->origin, part2);
}
