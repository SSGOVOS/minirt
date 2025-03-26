/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:43:52 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/26 19:43:53 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	length;
	char	*sub;

	i = start;
	j = 0;
	length = ft_strlen(s);
	if (s == NULL || start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > length - start)
		len = length - start;
	sub = (char *)malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (s[i] && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
