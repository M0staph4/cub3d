/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:12 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/07 18:32:32 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hitwall(t_cub *data, double x, double y)
{
	if (data->map[(int)y / data->i_2d][(int)x / data->i_2d] == '0')
		return (1);
	return (0);
}

int	player_hitwall(t_cub *data, int key)
{
	int	i;
	int	j;

	if (key == KEY_A || key == KEY_D)
	{
		i = data->xpos + cos(data->rotation_angle + 1.57) * data->move_step;
		j = data->ypos + sin(data->rotation_angle + 1.57) * data->move_step;
	}
	else
	{
		i = data->xpos + cos(data->rotation_angle) * data->move_step;
		j = data->ypos + sin(data->rotation_angle) * data->move_step;
	}
	if (data->map[(j - 1) / data->i_2d][(i / data->i_2d)] != '0'
		|| data->map[(j) / data->i_2d][((i + 1) / data->i_2d)] != '0'
		|| data->map[(j + 1) / data->i_2d][(i / data->i_2d)] != '0'
		|| data->map[j / data->i_2d][((i - 1) / data->i_2d)] != '0'
		|| data->map[(j - 1) / data->i_2d][((i + 1) / data->i_2d)] != '0'
		|| data->map[(j + 1) / data->i_2d][((i - 1) / data->i_2d)] != '0'
		|| data->map[(j - 1) / data->i_2d][i / data->i_2d] != '0'
		|| data->map[j / data->i_2d][(i / data->i_2d)] != '0')
	{
		printf("%d\n", j / data->i_2d);
		return (0);
	}
	return (1);
}

int	side_wall_collision(t_cub *data)
{
	int	i;
	int	j;

	i = data->xpos + cos(data->rotation_angle + 1.57) * data->move_step;
	j = data->ypos + sin(data->rotation_angle + 1.57) * data->move_step;
	if (data->map[j / data->i_2d][i / data->i_2d] == '0')
		return (1);
	return (0);
}

void	player_init(t_cub *data)
{
	data->side = 0;
	data->walk = 0;
	data->move_speed = 6;
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
