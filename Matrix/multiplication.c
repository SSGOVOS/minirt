/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:50:11 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:50:12 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_matrix	*mt_multiplication(t_matrix *mt1, t_matrix *mt2)
{
	t_matrix	*result;
	int			i;
	int			j;
	int			k;

	i = 0;
	if (!mt1 || !mt2 || mt1->cols != mt2->rows)
		return (NULL);
	result = create_matrix(mt1->rows, mt2->cols);
	while (i < mt1->rows)
	{
		k = 0;
		while (k < mt2->cols)
		{
			j = 0;
			while (j < mt1->cols)
			{
				result->matrix[i][k] += (mt1->matrix[i][j] * mt2->matrix[j][k]);
				j++;
			}
			k++;
		}
		i++;
	}
	return (result);
}

t_matrix	*safe_matrix_multy(t_matrix *mt1, t_matrix *mt2)
{
	t_matrix	*result;

	if (!mt1 || !mt2)
		return (NULL);
	result = mt_multiplication(mt1, mt2);
	delete_matrix(mt1);
	delete_matrix(mt2);
	if (!result)
		printf("error in safe mt \n");
	return (result);
}
