/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:21 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/04 12:46:03 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				return (PI3);
			else if (data->map[j][i] == 'W')
				return (PI);
			else if (data->map[j][i] == 'S')
				return (PI / 2);
			else if (data->map[j][i] == 'E')
				return (0);
			i++;
		}
		j++;
	}
	return (0);
}

void	get_address(t_texture *tex)
{
	tex->img[0].addr = (unsigned int *)mlx_get_data_addr(tex->img[0].texture,
			&tex->img[0].bpp, &tex->img[0].line, &tex->img[0].endian);
	tex->img[1].addr = (unsigned int *)mlx_get_data_addr(tex->img[1].texture,
			&tex->img[1].bpp, &tex->img[1].line, &tex->img[1].endian);
	tex->img[2].addr = (unsigned int *)mlx_get_data_addr(tex->img[2].texture,
			&tex->img[2].bpp, &tex->img[2].line, &tex->img[2].endian);
	tex->img[3].addr = (unsigned int *)mlx_get_data_addr(tex->img[3].texture,
			&tex->img[3].bpp, &tex->img[3].line, &tex->img[3].endian);
}

void	load_texture(t_cub *data)
{
	int		x;
	int		y;

	data->tex.img[0].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[0], &x, &y);
	if (!data->tex.img[0].texture)
		xpm_error();
	data->tex.img[1].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[1], &x, &y);
	if (!data->tex.img[1].texture)
		xpm_error();
	data->tex.img[2].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[2], &x, &y);
	if (!data->tex.img[2].texture)
		xpm_error();
	data->tex.img[3].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[3], &x, &y);
	if (!data->tex.img[3].texture)
		xpm_error();
	get_address(&data->tex);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*pixel;

	pixel = data->addr + (y * data->line + x * (data->bpp / 8));
	*(int *)pixel = color;
}

int	get_pixel_color(t_texture *tex)
{
	if (tex->texpos == 1)
		return (tex->img[1].addr[tex->img[1].line / (tex->img[1].bpp / 8)
				* tex->tex_x + tex->tex_y]);
	if (tex->texpos == 4)
		return (tex->img[3].addr[tex->img[3].line / (tex->img[3].bpp / 8)
				* tex->tex_x + tex->tex_y]);
	if (tex->texpos == 3)
		return (tex->img[0].addr[tex->img[0].line / (tex->img[0].bpp / 8)
				* tex->tex_x + tex->tex_y]);
	return (tex->img[2].addr[tex->img[2].line / (tex->img[2].bpp / 8)
			* tex->tex_x + tex->tex_y]);
}
