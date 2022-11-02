/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:12 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/01 23:01:35 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hitwall(t_cub *data, double x, double y)
{
	if (data->map[(int)y / data->i_2d][(int)x / data->i_2d] == '0')
		return (1);
	return (0);
}

int	check_wall_collision(t_cub *data)
{
	int	i;
	int	j;

	i = data->xpos + cos(data->rotation_angle) * data->move_step;
	j = data->ypos + sin(data->rotation_angle) * data->move_step;
	if (data->map[j / data->i_2d][i / data->i_2d] == '0')
		return (1);
	return (0);
}

double	check_direction(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N')
				return (PI / 2);
			else if (data->map[j][i] == 'W')
				return (PI);
			else if (data->map[j][i] == 'S')
				return (PI3);
			else if (data->map[j][i] == 'E')
				return (0);
			i++;
		}
		j++;
	}
	return (0);
}

void	player_init(t_cub *data)
{
	data->side = 0;
	data->walk = 0;
	data->move_speed = 10;
	data->rotation_angle = check_direction(data);
	data->rotation_speed = 6 * (PI / 180);
}

void	player_pos(t_cub *data)
{
	int	i;
	int	j;

	j = 0;
	player_init(data);
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N' || data->map[j][i] == 'E'
				|| data->map[j][i] == 'S' || data->map[j][i] == 'W')
			{
				data->map[j][i] = '0';
				data->xpos = i * data->i_2d;
				data->ypos = j * data->i_2d;
			}
			i++;
		}
		j++;
	}
}
