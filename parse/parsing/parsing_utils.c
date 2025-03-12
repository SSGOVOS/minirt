#include "../../main.h"

int array_length(char **arr)
{
	int length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

int arg_error(char *msg)
{
	printf("Error: too many arguments for %s\n", msg);
	return (0);
}

void ft_add_back(t_object_parse **list, t_object_parse *new, int type)
{
	t_object_parse *temp;

	if (new == NULL)
		return;
	new->type = type;
	if (*list == NULL)
	{
		*list = new;
		new->next = NULL;
	}
	else
	{
		temp = *list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

void free_array_parse(char *arr[])
{
	int i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void free_objects_parse(t_object_parse *object)
{
	t_object_parse *temp;

	while (object)
	{
		temp = object;
		object = object->next;
		//		if (temp->type == SPHERE)
		free(temp->object);
		free(temp);
	}
}