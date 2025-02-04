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
		i++;
	}
}

// parse to get this
void list_object(t_vars* vars)
{
	vars->objects = malloc(sizeof(t_object) * vars->obj_count);
	vars->objects[0].type = SPHERE;
	vars->objects[0].base_color = (t_vec3){1, 0, 0}; // red
	vars->objects[0].radius = 2;
	vars->objects[0].translation = (t_vec3) {0, 0, -0.5};
	// plane
	// t_object *plane = malloc(sizeof(t_object));
	// plane->type = PLANE;
	// plane->base_color = (t_vec3) {0.5, 0.5, 0.5}; // gray
	// plane->translation = (t_vec3) {-1, 0, 0};
	// plane->d_normal = (t_vec3) {1, 0, 0};
	// plane->next = NULL;
	vars->objects[1].type = PLANE;
	vars->objects[1].base_color = (t_vec3) {0.5, 0.5, 0.5}; // gray
	vars->objects[1].translation = (t_vec3) {0, 0, 1.5};
	vars->objects[1].d_normal = (t_vec3) {0, 0, -1};
	prepare_objects(vars->objects, 2);
}
