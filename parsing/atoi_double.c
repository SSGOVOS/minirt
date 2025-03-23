/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelbassa <zelbassa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:13:10 by zelbassa          #+#    #+#             */
/*   Updated: 2025/03/23 22:31:38 by zelbassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	parse_fraction(char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			fraction = fraction * 10.0 + (**str - '0');
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (fraction / divisor);
}

double	atoi_double(char *str)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	if (ft_atoi(str) > INT_MAX)
		return (0.0);
	while (*str == ' ')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	result += parse_fraction(&str);
	result *= sign;
	return (result);
}

int	is_float(const char *c)
{
	int	i;
	int	float_flag;

	i = 0;
	float_flag = 0;
	while (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i])
	{
		if (c[i] == '.')
		{
			if (float_flag)
				return (0);
			float_flag = 1;
		}
		else if (!ft_isdigit(c[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*append_buff(char *line, char *buff)
{
	char	*temp;

	if (!line)
		return (ft_strdup(buff));
	temp = ft_strjoin(line, buff);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (temp);
}

char	*get_next_line(int fd)
{
	char	buff[2];
	char	*line;
	ssize_t	bytes_read;

	line = NULL;
	bytes_read = read(fd, buff, 1);
	while (bytes_read > 0)
	{
		if (bytes_read < 0)
			break ;
		buff[1] = '\0';
		line = append_buff(line, buff);
		if (!line)
			return (NULL);
		if (buff[0] == '\n')
			break ;
		bytes_read = read(fd, buff, 1);
	}
	if (bytes_read < 0)
		return (free(line), NULL);
	return (line);
}
