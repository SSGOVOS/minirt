/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:13:25 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/25 15:34:43 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	array_length(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

int	arg_error(char *msg)
{
	printf("Error: wrong number of arguments %s\n", msg);
	return (0);
}

void	ft_add_back(t_object_parse **list, t_object_parse *new, int type)
{
	t_object_parse	*temp;

	if (new == NULL)
		return ;
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

void	free_array_parse(char *arr[])
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	free_objects_parse(t_object_parse *object)
{
	t_object_parse	*temp;

	if (!object)
		return ;
	while (object)
	{
		temp = object;
		object = object->next;
		free(temp->object);
		free(temp);
	}
}
