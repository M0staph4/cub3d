/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:52:02 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/03 22:24:06 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_zero(char **map, int j, int i)
{
	if (ft_strlen(map[j + 1]) <= (size_t)i
		|| ft_strlen(map[j - 1]) <= (size_t)i)
		return (0);
	if (map[j][i + 1] == ' ' || map[j][i - 1] == ' ')
		return (0);
	if (map[j - 1][i] == ' ' || map[j + 1][i] == ' ')
		return (0);
	return (1);
}

int	check_spaces(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'W'
				|| map[j][i] == 'S' || map[j][i] == 'E')
			{
				if (!check_zero(map, j, i))
					return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	is_close(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (map[0][i] && (map[0][i] == '1' || map[0][i] == ' '))
		i++;
	if ((size_t)i != ft_strlen(map[0]))
		return (0);
	i = 0;
	while (map[++j])
	{
		while (map[j][i] == ' ')
			i++;
		if (map[j][i] != '1' && map[j][ft_strlen(map[j]) - 1] != '1')
			return (0);
		i = 0;
	}
	while (map[j - 1][i] && (map[j - 1][i] == '1' || map[j - 1][i] == ' '))
		i++;
	if ((size_t)i != ft_strlen(map[j - 1]))
		return (0);
	if (!check_spaces(map))
		return (0);
	return (1);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!check_player(map))
		return (0);
	if (!is_close(map))
		return (0);
	return (1);
}

int	check_map(t_cub *data)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (data->file[i])
		i++;
	data->map = malloc(sizeof(char *) * (i - 5));
	data->map[i - 6] = NULL;
	i = 6;
	while (data->file[i])
		data->map[x++] = ft_strdup(data->file[i++]);
	if (!check_walls(data->map))
		return (0);
	return (1);
}
