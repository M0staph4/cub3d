#include "cub3d.h"

int HitWall(t_cub *data, double x, double y)
{
	if (data->map[(int)y / data->i_2D][(int)x / data->i_2D] == '0')
		return(1);
	return(0);
}

void	render_line(t_cub *data, double deltaX, double deltaY, double ray, int c)
{
	double	step;

	if (fabs(deltaX) > fabs(deltaY))
		step = fabs(deltaX);
	else
		step = fabs(deltaY);
	data->pixelX = data->xpos;
	data->pixelY = data->ypos;
	deltaX /= step;
	deltaY /= step;
	(void)c;
	while (HitWall(data, data->pixelX, data->pixelY))
	{	
		if (!c)
	    	pixel_put(&data->img_3D, (data->pixelX / data->i_2D) * 20, (data->pixelY / data->i_2D) * 20, 0x0000FF);
	    data->pixelX += deltaX;
	    data->pixelY += deltaY;
	}
	data->player_dis = sqrt(pow(data->pixelX - data->xpos, 2) + pow(data->pixelY - data->ypos, 2)) * cos((ray - data->rotation_angle));
	data->projection_plane = (WINDOW_WIDTH / 2) / tan((64 * (PI / 180)) / 2);
	data->wall = (data->i_2D / data->player_dis) * data->projection_plane;
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
		pixel_put(&data->img_3D, (data->xpos / data->i_2D) * 20 + x1, (data->ypos / data->i_2D) * 20 + y1, 0x0000FF);
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

void	render_fov(t_cub *data)
{
	double	l;

	l = data->rotation_angle;
	render_line(data,(data->xpos + cos(l)) - data->xpos,(data->ypos + sin(l)) - data->ypos, 1, 0);
}

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
	render_fov(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img_3D.mlx_img, 0, 0);
}