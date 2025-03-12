#include "main.h"


void handle_cylinder();

void prepare_objects(t_object *list, int obj_count)
{
	int i = 0;
	while (i < obj_count)
	{
		if (list[i].type == SPHERE)
		{
			list[i].rotation = (t_vec3){0, 0, 0};
			list[i].scale = (t_vec3) {list[i].radius,list[i].radius, list[i].radius};
			list[i].gtfm = set_transform(&list[i].translation, &list[i].rotation, &list[i].scale);
			list[i].intersect = test_sphere;
		}
		else if (list[i].type == PLANE)
		{
			list[i].d_normal = normalize(list[i].d_normal);
			list[i].intersect = test_plane;
		}
		else if (list[i].type == CYLINDER)
		{
			list[i].d_normal = normalize(list[i].d_normal);
			list[i].rotation = get_rotation_vector(list[i].d_normal);
			list[i].scale = (t_vec3){list[i].radius, list[i].radius, 2};
			list[i].gtfm = set_transform(&list[i].translation, &list[i].rotation, &list[i].scale);
			list[i].intersect = test_cylinder;
		}
		i++;
	}
}

// parse to get this
void list_object(t_vars* vars)
{
	
	vars->objects = malloc(sizeof(t_object) * vars->obj_count);
	vars->objects[0].type = SPHERE;
	vars->objects[0].base_color = (t_vec3){1, 0, 0}; // red
	vars->objects[0].radius = 1.5;
	vars->objects[0].translation = (t_vec3) {-3, -3, -0.5};
	// plane
	// t_object *plane = malloc(sizeof(t_object));
	vars->objects[3].type = SPHERE;
	vars->objects[3].base_color = (t_vec3){0, 1, 0}; // red
	vars->objects[3].radius = 0.5;
	vars->objects[3].translation = (t_vec3) {-5, -6, -0.5};

	vars->objects[1].type = PLANE;
	vars->objects[1].base_color = (t_vec3) {1, 1, 1}; // gray
	vars->objects[1].translation = (t_vec3) {0, 0, 1.5};
	vars->objects[1].d_normal = (t_vec3) {0, 0, 1};
	// cylinder
	vars->objects[2].type = CYLINDER;
	vars->objects[2].base_color = (t_vec3){0, 1, 1}; // blue
	vars->objects[2].radius = 1;
	vars->objects[2].translation = (t_vec3) {2, -4, -1.5};
	vars->objects[2].d_normal = (t_vec3) {0 ,0, 1};

	prepare_objects(vars->objects, vars->obj_count);
}
