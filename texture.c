#include "cub3d.h"

void	load_texture(t_cub *data)
{
	int		x;
	int		y;

	data->tex.img[0].texture = mlx_xpm_file_to_image(data->mlx, data->xpm_file[0], &x, &y);
	data->tex.img[0].addr =  (unsigned int *)mlx_get_data_addr(data->tex.img[0].texture, &data->tex.img[0].bpp, &data->tex.img[0].line, &data->tex.img[0].endian);
	data->tex.img[1].texture = mlx_xpm_file_to_image(data->mlx, data->xpm_file[1], &x, &y);
	data->tex.img[1].addr =  (unsigned int *)mlx_get_data_addr(data->tex.img[1].texture, &data->tex.img[1].bpp, &data->tex.img[1].line, &data->tex.img[1].endian);
	data->tex.img[2].texture = mlx_xpm_file_to_image(data->mlx, data->xpm_file[2], &x, &y);
	data->tex.img[2].addr =  (unsigned int *)mlx_get_data_addr(data->tex.img[2].texture, &data->tex.img[2].bpp, &data->tex.img[2].line, &data->tex.img[2].endian);
	data->tex.img[3].texture = mlx_xpm_file_to_image(data->mlx, data->xpm_file[3], &x, &y);
	data->tex.img[3].addr =  (unsigned int *)mlx_get_data_addr(data->tex.img[3].texture, &data->tex.img[3].bpp, &data->tex.img[3].line, &data->tex.img[3].endian);
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line + x * (data->bpp / 8));
	*(int*)dst = color;
}

int	get_pixel_color(t_texture *tex)
{
	if (tex->texPos == 1)
		return (tex->img[0].addr[tex->img[0].line / (tex->img[0].bpp / 8) * tex->texX + tex->texY]);
	if (tex->texPos == 2)
		return (tex->img[1].addr[tex->img[1].line / (tex->img[1].bpp / 8) * tex->texX + tex->texY]);
	if (tex->texPos == 3)
		return (tex->img[2].addr[tex->img[2].line / (tex->img[2].bpp / 8) * tex->texX + tex->texY]);
	return (tex->img[3].addr[tex->img[3].line / (tex->img[3].bpp / 8) * tex->texX + tex->texY]);
}
