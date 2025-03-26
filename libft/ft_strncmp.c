/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:43:13 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/26 19:43:14 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (1);
	if (n == 0)
	{
		while (*s1 && *s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
	}
	else
	{
		while (*s1 == *s2 && *s1 && *s2 && n > 1)
		{
			s1++;
			s2++;
			n--;
		}
	}
	return (((unsigned char)(*s1) - (unsigned char)(*s2)));
}
