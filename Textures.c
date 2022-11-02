/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:23:21 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/01 20:54:37 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void free_txt(t_cub *data)
{
	int i;
	i = -1;
	while(data->xpm_file[++i])
		free(data->xpm_file[i]);
	free(data->xpm_file);
}

void	load_texture(t_cub *data)
{
	int		x;
	int		y;

	data->tex.img[0].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[0], &x, &y);
	if (!data->tex.img[0].texture)
		exit(0);
	data->tex.img[1].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[1], &x, &y);
	if (!data->tex.img[1].texture)
		exit(0);
	data->tex.img[2].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[2], &x, &y);
	if (!data->tex.img[2].texture)
		exit(0);
	data->tex.img[3].texture = mlx_xpm_file_to_image(data->mlx,
			data->xpm_file[3], &x, &y);
	if (!data->tex.img[3].texture)
		exit(0);
	get_address(&data->tex);
	//free_txt(data);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line + x * (data->bpp / 8));
	*(int *)dst = color;
}

int	get_pixel_color(t_texture *tex)
{
	if (tex->texpos == 1)
		return (tex->img[0].addr[tex->img[0].line / (tex->img[0].bpp / 8)
				* tex->tex_x + tex->tex_y]);
	if (tex->texpos == 2)
		return (tex->img[1].addr[tex->img[1].line / (tex->img[1].bpp / 8)
				* tex->tex_x + tex->tex_y]);
	if (tex->texpos == 3)
		return (tex->img[2].addr[tex->img[2].line / (tex->img[2].bpp / 8)
				* tex->tex_x + tex->tex_y]);
	return (tex->img[3].addr[tex->img[3].line / (tex->img[3].bpp / 8)
			* tex->tex_x + tex->tex_y]);
}
