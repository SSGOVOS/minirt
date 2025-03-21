/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:50:06 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:50:08 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	copy_clmn(float *clm1, float *clm2, int column, int size)
{
	int	j;
	int	fci;

	j = 0;
	fci = 0;
	while (j < size)
	{
		if (j != column)
		{
			clm1[fci] = clm2[j];
			fci++;
		}
		j++;
	}
}

t_matrix	*submatrix(t_matrix *mt, int row, int column)
{
	int			i;
	int			fri;
	t_matrix	*new_matrix;

	if (mt->rows <= 1 || mt->cols <= 1)
		return (mt);
	new_matrix = create_matrix(mt->rows - 1, mt->rows - 1);
	i = 0;
	fri = 0;
	while (i < mt->rows)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		copy_clmn(new_matrix->matrix[fri], mt->matrix[i], column, mt->cols);
		fri++;
		i++;
	}
	return (new_matrix);
}

float	minor(t_matrix *mt, int row, int column)
{
	t_matrix	*sub;
	float		m_determinant;

	sub = submatrix(mt, row, column);
	m_determinant = determinant(sub);
	delete_matrix(sub);
	return (m_determinant);
}
