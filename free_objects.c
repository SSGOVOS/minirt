/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 06:16:15 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/20 06:16:18 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_objects(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->obj_count)
	{
		if (vars->objects[i].type == SPHERE
			|| vars->objects[i].type == CYLINDER)
		{
			delete_matrix(vars->objects[i].gtfm[0]);
			delete_matrix(vars->objects[i].gtfm[1]);
			free(vars->objects[i].gtfm);
		}
		i++;
	}
	free(vars->objects);
}

void	free_image(t_image *image)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		free(image->red[i]);
		free(image->green[i]);
		free(image->blue[i]);
		i++;
	}
	free(image->red);
	free(image->green);
	free(image->blue);
	free(image);
}
