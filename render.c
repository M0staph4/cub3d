#include "cub3d.h"


int line_length(t_cub *data, double x, double y)
{
	if (data->map[(int)y / data->i_2D][(int)x / data->i_2D] == '1')
		return(0);
	return(1);
}

void	render_line(t_cub *data, double deltaX, double deltaY, int color, int c, int ray)
{
	int		pixels;

	data->pixelX = data->xpos;
	data->pixelY = data->ypos;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	(void)c;
	while (line_length(data, data->pixelX, data->pixelY))
	{	
	    pixel_put(&data->img_3D, (data->pixelX / data->i_2D) * 20, (data->pixelY / data->i_2D) * 20, color);
	    data->pixelX += deltaX;
	    data->pixelY += deltaY;
	}
	data->player_dis = sqrt(pow(data->xpos - data->pixelX , 2) + pow(data->ypos - data->pixelY, 2)) * cos(ray);
    data->wall = (data->i_2D * WINDOW_HEIGHT) / data->player_dis;
	(void)ray;

}

void	render_player(t_cub *data, int r)
{
	double	angle;
	double	x1;
	double	y1;
	angle = 0;
	(void)data;
	while (angle < 360)
	{
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		pixel_put(&data->img_3D, (data->xpos / data->i_2D) * 20 + x1, (data->ypos / data->i_2D) * 20 + y1, 0x40E0D0);
		angle += 0.01;
	}
}

void	render_square(t_cub *data, int x, int y, int color)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(i < (20))
	{
		j = 0;
		while (j < 20)
		{
			pixel_put(&data->img_3D, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// void	render_fov(t_cub *data)
// {
// 	double	x;
// 	double	l;

// 	x = -32;
// 	l = data->rotation_angle;
// 	double xx, y;
// 	xx = (data->xpos / data->i_2D) * 20;
// 	y = (data->ypos / data->i_2D) * 20;
// 	while (x < 32)
// 	{
// 		render_line(data,(xx + cos(l + x) * 1000) - xx,(y + sin(l + x) * 1000) - y,  0xCCC899, 1, 0);
// 		x += 0.064 / 50;
// 	}
// 	render_line(data,(data->xpos + cos(l) * 1000) - data->xpos,(data->ypos + sin(l) * 1000) - data->ypos,  0xE04080, 1, 0);
// }

void	render_map(t_cub *data)
{
	int i;
	int j;

	j = 0;
	raycasting(data);
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				render_square(data,  20 * i, 20 * j, 0x3F4A4F);
			i++;
		}
		j++;
	}
	render_player(data, 5);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_3D.mlx_img, 0, 0);
	// mlx_destroy_image(data->mlx, data->img_3D.mlx_img);
}