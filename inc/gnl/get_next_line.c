/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <cel-mhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:37:58 by mmoutawa          #+#    #+#             */
/*   Updated: 2022/10/22 20:15:24 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_zron(char *u)
{
	int		i;

	i = 0;
	if (!u)
		return (0);
	while (u[i])
	{
		if (u[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_nxln(char *p)
{
	int		i;
	char	*u;

	i = 0;
	if (!p)
		return (NULL);
	while (p[i])
	{
		if (p[i] == '\n' || p[i] == '\0')
		{
			u = ftg_substr(p, i + 1, ftg_strlen(p) - i);
			free (p);
			return (u);
		}
		i++;
	}
	free(p);
	return (NULL);
}

char	*ft_cln(char *res)
{
	int	i;

	i = 0;
	if (!res[0])
		return (NULL);
	while (res[i] && res[i] != '\n')
		i++;
	return (ftg_substr(res, 0, i + 1));
}

char	*ft_rdln(int fd, char *u)
{
	char	*p;
	int		x;

	x = 1;
	p = NULL;
	p = malloc(10 + 1);
	if (!p)
		return (NULL);
	while (!ft_zron(u) && x)
	{
		x = read(fd, p, 1);
		if (x == -1)
		{
			free(p);
			return (NULL);
		}
		p[x] = '\0';
		u = ftg_strjoin(u, p);
	}
	free (p);
	return (u);
}

char	*get_next_line(int fd)
{
	static char	*u;
	char		*p;

	if (fd < 0)
		return (NULL);
	u = ft_rdln(fd, u);
	if (!u)
		return (NULL);
	p = ft_cln(u);
	u = ft_nxln(u);
	return (p);
}
