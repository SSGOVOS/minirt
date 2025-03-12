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
			list[i].scale = (t_vec3){list[i].radius, list[i].radius, list[i].height};
			list[i].gtfm = set_transform(&list[i].translation, &list[i].rotation, &list[i].scale);
			list[i].intersect = test_cylinder;
		}
		i++;
	}
}

// parse to get this
void list_object(t_vars* vars, t_rt *rt)
{
	
	vars->objects = malloc(sizeof(t_object) * rt->object_count);
	vars->obj_count = rt->object_count;
	int i = 0;
	t_object_parse *head = rt->object;
	while (head)
	{
		if (head->type == SPHERE_PARSE)
		{
			t_sphere *sphere = (t_sphere*)(head);
			vars->objects[i].type = SPHERE;
			vars->objects[i].translation = (t_vec3){sphere->position.x, sphere->position.y, sphere->position.z};
			vars->objects[i].base_color = (t_vec3){sphere->color.r, sphere->color.g, sphere->color.b};
			vars->objects[i].radius = (float)(sphere->diameter) / 2.0f;
		}
		else if (head->type == PLANE_PARSE)
		{
			t_plane *plane = (t_plane*)(head);
			vars->objects[i].type = PLANE;
			vars->objects[i].translation = (t_vec3){plane->position.x, plane->position.y, plane->position.z};
			vars->objects[i].base_color = (t_vec3){plane->color.r, plane->color.g, plane->color.b};
			vars->objects[i].d_normal = (t_vec3){plane->direction.x, plane->direction.y, plane->direction.z};
		}
		else if (head->type == CYLINDER_PARSE)
		{
			t_cylinder *cylinder = (t_cylinder*)(head);
			vars->objects[i].type = CYLINDER;
			vars->objects[i].translation = (t_vec3){cylinder->position.x, cylinder->position.y, cylinder->position.z};
			vars->objects[i].base_color = (t_vec3){cylinder->color.r, cylinder->color.g, cylinder->color.b};
			vars->objects[i].radius = (float)(cylinder->diameter) / 2.0f;
			vars->objects[i].height = cylinder->height;
			vars->objects[i].d_normal = (t_vec3){cylinder->direction.x, cylinder->direction.y, cylinder->direction.z};
		}
		i++;
		head = head->next;
	}
	prepare_objects(vars->objects, vars->obj_count);
}
