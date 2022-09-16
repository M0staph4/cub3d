/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 04:08:01 by cel-mhan          #+#    #+#             */
/*   Updated: 2021/12/07 04:17:50 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ftg_strchr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*current_line(char *rest)
{
	int	i;

	i = 0;
	if (!rest[0])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	return (ftg_substr(rest, 0, i + 1));
}

char	*next_line(char *rest)
{
	int		i;
	char	*x;

	i = 0;
	if (!rest)
		return (NULL);
	while (rest[i])
	{
		if (rest[i] == '\n')
		{
			x = ftg_substr(rest, i + 1, ftg_strlen(rest));
			free(rest);
			return (x);
		}
		i++;
	}
	free(rest);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char			buff[2];
	static char		*rest;
	char			*line;
	int				c;

	c = 1;
	line = NULL;
	if (fd < 0)
		return (0);
	while (c && ftg_strchr(rest))
	{
		c = read(fd, buff, 1);
		if (c == -1)
			return (line);
		buff[c] = '\0';
		rest = ftg_strjoin(rest, buff);
	}
	line = current_line(rest);
	rest = next_line(rest);
	return (line);
}
