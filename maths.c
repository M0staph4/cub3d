/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:52:32 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/03 22:24:16 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	player_distance(t_cub *data, double angle)
{
	return (sqrt(pow(data->pixelx - data->xpos, 2)
			+ pow(data->pixely - data->ypos, 2))
		* cos((angle - data->rotation_angle)));
}

double	projection_plane(void)
{
	return ((WINDOW_WIDTH / 2) / tan((64 * (PI / 180)) / 2));
}

double	wall_height(t_cub *data)
{
	return ((data->i_2d / data->player_dis) * data->projection_plane);
}
