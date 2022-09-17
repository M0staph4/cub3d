#include "cub3d.h"

void	render_line(t_cub *data, int color)
{
	double deltaX;
	double deltaY;
	double pixelX = data->xpos;
	double pixelY = data->ypos;
	
	deltaX = (data->xpos + cos(data->rotation_angle) * 50) - data->xpos;
	deltaY = (data->ypos + sin(data->rotation_angle) * 50) - data->ypos;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
	    mlx_pixel_put(data->mlx, data->mlx_win, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	    --pixels;
	}
}

void	render_player(t_cub *data, int r)
{
	double angle = 0, x1, y1;
	while(angle < 360)
	{
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		mlx_pixel_put(data->mlx, data->mlx_win, (data->xpos) + x1, (data->ypos) + y1, 0xFFFFFF);
		angle += 0.1;
	}
}

void	render_square(t_cub *data, int x, int y, int color)
{
	int i = 0, j = 0;
	while(i < 50)
	{
		j = 0;
		while(j < 50)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_cub *data)
{
	int i;
	int j = 0;

	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if(data->map[j][i] == '1')
				render_square(data, i * 50, j * 50, 0xFFFFFF);
			else if(data->map[j][i] == '0')
				render_square(data, i * 50, j * 50, 0x000000);
			i++;
		}
		j++;
	}
	render_line(data, 0xFFFFFF);
	render_player(data, 5);
}