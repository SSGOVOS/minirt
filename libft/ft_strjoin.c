/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:42:44 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/26 19:42:45 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *line, char *buf)
{
	char	*join;

	if (!line || !buf)
	{
		if (line)
			return (ft_strdup(line));
		if (buf)
			return (ft_strdup(buf));
		return (NULL);
	}
	join = (char *)malloc(ft_strlen(line) + ft_strlen(buf) + 1);
	if (!join)
		return (NULL);
	join[0] = '\0';
	if (line)
		ft_strlcat(join, line, ft_strlen(line) + 1);
	if (buf)
		ft_strlcat(join, buf, ft_strlen(buf) + ft_strlen(line) + 1);
	if (!join[0])
		return (free(join), NULL);
	return (join);
}
