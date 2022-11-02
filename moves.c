/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:08 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/10/31 23:44:41 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_cub *data)
{
	data->walk = 1;
	data->move_step = data->walk * data->move_speed;
	if (check_wall_collision(data))
	{
		data->xpos += cos(data->rotation_angle) * data->move_step;
		data->ypos += sin(data->rotation_angle) * data->move_step;
		render_map(data);
	}
}

void	move_down(t_cub *data)
{
	data->walk = -1;
	data->move_step = data->walk * data->move_speed;
	if (check_wall_collision(data))
	{
		data->xpos += cos(data->rotation_angle) * data->move_step;
		data->ypos += sin(data->rotation_angle) * data->move_step;
		render_map(data);
	}
}

void	rotate_left(t_cub *data)
{
	data->side = -1;
	data->rotation_angle += data->side * data->rotation_speed;
	render_map(data);
}

void	rotate_right(t_cub *data)
{
	data->side = 1;
	data->rotation_angle += data->side * data->rotation_speed;
	render_map(data);
}

void	move_right_left(t_cub *data, int key)
{
	if (key == KEY_D)
		data->walk = 1;
	else if (key == KEY_A)
		data->walk = -1;
	data->move_step = data->walk * data->move_speed;
	if (check_wall_collision(data))
	{
			data->xpos += cos(data->rotation_angle + 1.57) * data->move_step;
			data->ypos += sin(data->rotation_angle + 1.57) * data->move_step;
		render_map(data);
	}
}
