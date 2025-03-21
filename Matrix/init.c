/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:49:39 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:49:42 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	fill_mt(t_matrix *mt, float *values)
{
	int	k;
	int	i;
	int	j;

	k = 0;
	i = 0;
	while (i < mt->rows)
	{
		j = 0;
		while (j < mt->cols)
		{
			mt->matrix[i][j] = values[k++];
			j++;
		}
		i++;
	}
}

float	*create_cols(int c)
{
	int		i;
	float	*new_col;

	i = 0;
	new_col = malloc(c * sizeof(float));
	while (i < c)
		new_col[i++] = .0;
	return (new_col);
}

t_matrix	*create_matrix(int rows, int cols)
{
	t_matrix	*new_mt;
	int			i;
	float		**mt;

	if (rows <= 0 || cols <= 0)
		return (NULL);
	new_mt = malloc(sizeof(t_matrix));
	i = 0;
	new_mt->rows = rows;
	new_mt->cols = cols;
	mt = malloc(sizeof(float *) * rows);
	while (i < rows)
		mt[i++] = create_cols(cols);
	new_mt->matrix = mt;
	return (new_mt);
}
