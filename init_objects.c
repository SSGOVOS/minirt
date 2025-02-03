#include "main.h"


void handle_cylinder();

void prepare_objects(t_object *list)
{
	t_object *head = list;
	
	while (head)
	{
		if (head->type == SPHERE)
		{
			head->rotation = (t_vec3){0, 0, 0};
			head->scale = (t_vec3) {head->radius,head->radius, head->radius};
			head->gtfm = set_transform(&head->translation, &head->rotation, &head->scale);
			head->intersect = test_sphere;
		}
		else if (head->type == PLANE)
		{
			head->d_normal = normalize(head->d_normal);
			head->intersect = test_plane;
		}
		head = head->next;
	}
}

t_object	*ft_lstlast(t_object *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_object **lst, t_object *new)
{
	t_object	*node;

	if (new)
	{
		if (*lst)
		{
			node = ft_lstlast(*lst);
			node->next = new;
		}
		else
			*lst = new;
	}
}


// parse to get this
t_object *list_object()
{
	t_object *list = NULL;
	t_object *sphere = malloc(sizeof(t_object));
	sphere->type = SPHERE;
	sphere->base_color = (t_vec3){1, 0, 0}; // red
	sphere->radius = 2;
	sphere->translation = (t_vec3) {0, 0, -0.5};
	sphere->next = NULL;
	// plane
	// t_object *plane = malloc(sizeof(t_object));
	// plane->type = PLANE;
	// plane->base_color = (t_vec3) {0.5, 0.5, 0.5}; // gray
	// plane->translation = (t_vec3) {-1, 0, 0};
	// plane->d_normal = (t_vec3) {1, 0, 0};
	// plane->next = NULL;
	t_object *plane2 = malloc(sizeof(t_object));
	plane2->type = PLANE;
	plane2->base_color = (t_vec3) {0.5, 0.5, 0.5}; // gray
	plane2->translation = (t_vec3) {0, 0, 1.5};
	plane2->d_normal = (t_vec3) {0, 0, -1};
	plane2->next = NULL;
	ft_lstadd_back(&list, sphere);
	// ft_lstadd_back(&list, plane);
	ft_lstadd_back(&list, plane2);
	prepare_objects(list);
	return (list);
}
