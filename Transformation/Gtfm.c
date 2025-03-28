/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gtfm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubine <amoubine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 07:33:02 by amoubine          #+#    #+#             */
/*   Updated: 2025/03/22 07:35:14 by amoubine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_matrix	**set_transform(t_vec3 *translation, t_vec3 *rotat, t_vec3 *scale)
{
	t_matrix	**result;
	t_matrix	*forward;

	if (!translation || !rotat || !scale)
	{
		printf("some thing null in set_transform \n");
		return (NULL);
	}
	result = malloc(sizeof(t_matrix *) * 2);
	forward = NULL;
	forward = safe_matrix_multy(translation_matrix(translation),
			rotation_matrix_x(rotat->x));
	forward = safe_matrix_multy(forward, rotation_matrix_y(rotat->y));
	forward = safe_matrix_multy(forward, rotation_matrix_z(rotat->z));
	forward = safe_matrix_multy(forward, scale_matrix(scale));
	result[0] = forward;
	result[1] = inverse(forward);
	return (result);
}

t_vec3	apply_transform_vector(t_vec3 inputVector, int dirFlag, t_matrix **gtfm)
{
	t_matrix	*tmp;
	float		*values;
	t_matrix	*resultmt;
	t_vec3		result;

	resultmt = NULL;
	values = (float []){inputVector.x, inputVector.y, inputVector.z, 1.0};
	tmp = create_matrix(4, 1);
	fill_mt(tmp, values);
	if (dirFlag)
		resultmt = mt_multiplication(gtfm[0], tmp);
	else
		resultmt = mt_multiplication(gtfm[1], tmp);
	if (!resultmt)
	{
		delete_matrix(tmp);
		return ((t_vec3){0.0, 0.0, 0.0});
	}
	result = (t_vec3){resultmt->matrix[0][0], resultmt->matrix[1][0],
		resultmt->matrix[2][0]};
	delete_matrix(resultmt);
	delete_matrix(tmp);
	return (result);
}

t_ray	apply_transform(t_ray *input_ray, t_matrix **gtfm, int dirFlag)
{
	t_ray	output;

	output.point1 = apply_transform_vector(input_ray->point1, dirFlag, gtfm);
	output.point2 = apply_transform_vector(input_ray->point2, dirFlag, gtfm);
	output.dir = normalize(vec_sub(output.point2, output.point1));
	return (output);
}
