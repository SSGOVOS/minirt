/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:41:19 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/26 19:41:20 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	void			*p;

	i = 0;
	p = (void *)s;
	while (i < n)
	{
		if (((unsigned char *)p)[i] == (unsigned char)c)
			return (p + i);
		i++;
	}
	return (NULL);
}
