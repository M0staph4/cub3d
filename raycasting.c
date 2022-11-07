/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:15 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/04 12:23:15 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	long_line(t_cub *data)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	i = 0;
	j = 0;
	while (data->map[j])
	{
		i = ft_strlen(data->map[j]);
		if (i > x)
			x = i;
		j++;
	}
	if (x < j)
		return (j);
	return (x);
}

int	rgb_to_color(t_cub *data, char c)
{
	if (c == 'C')
		return (((data->colors.r_c) << 16)
			+ ((data->colors.g_c) << 8) + (data->colors.b_c));
	else
		return (((data->colors.r_f) << 16)
			+ ((data->colors.g_f) << 8) + (data->colors.b_f));
}

int	direction(t_cub *data)
{
	int	y;
	int	x;

	x = data->pixelx / data->i_2d;
	y = data->pixely / data->i_2d;
	if (data->map[((int)data->pixely + 1) / data->i_2d][x] == '0')
		data->tex.texpos = 1;
	if (data->map[y][((int)data->pixelx + 1) / data->i_2d] == '0')
		data->tex.texpos = 2;
	if (data->map[((int)data->pixely - 1) / data->i_2d][x] == '0')
		data->tex.texpos = 3;
	if (data->map[y][((int)data->pixelx - 1) / data->i_2d] == '0')
		data->tex.texpos = 4;
	return (data->tex.texpos);
}

void	wall_projection(t_cub *data, int i)
{
	int		j;
	float	toppix;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		toppix = (WINDOW_HEIGHT - data->wall) / 2;
		if (direction(data) == 1 || direction(data) == 3)
			data->tex.tex_x = fmod(data->pixelx / 50, 1) * 50;
		if (direction(data) == 2 || direction(data) == 4)
			data->tex.tex_x = fmod(data->pixely / 50, 1) * 50;
		data->tex.tex_y = ((j - toppix) * 50) / data->wall;
		if (j < toppix)
			pixel_put(&data->img_3d, i, j, rgb_to_color(data, 'C'));
		else if (j < toppix + data->wall)
			pixel_put(&data->img_3d, i, j, get_pixel_color(&data->tex));
		else
			pixel_put(&data->img_3d, i, j, rgb_to_color(data, 'F'));
		j++;
	}
}

void	raycasting(t_cub *data)
{
	int		i;
	double	ray_angle;

	i = 0;
	ray_angle = -32;
	while (i < WINDOW_WIDTH)
	{
		if (ray_angle <= 32)
		{
			data->deltax = (data->xpos + cos(data->rotation_angle + ray_angle)
					* 1000) - data->xpos;
			data->deltay = (data->ypos + sin(data->rotation_angle + ray_angle)
					* 1000) - data->ypos;
			render_line(data,
				data->rotation_angle + ray_angle, 1);
		}
		wall_projection(data, i);
		i++;
		ray_angle += (64 * (PI / 180)) / WINDOW_WIDTH;
	}
}
