#include "cub3d.h"

void	render_line(t_cub *data, int beginX, int beginY, int endX, int endY)
{
	double deltaX;
	double deltaY;
	double pixelX = beginX;
	double pixelY = beginY;
	
	deltaX = endX - beginX;
	deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
	    mlx_pixel_put(data->mlx, data->mlx_win, pixelX, pixelY, 0xFFFFFF);
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
		mlx_pixel_put(data->mlx, data->mlx_win, (data->xpos * 50) + x1, (data->ypos * 50) + y1, 0xFFFFFF);
		angle += 0.1;
	}
}

void	render_square(t_cub *data, int x, int y)
{
	int i = 0, j = 0;
	while(i < 50)
	{
		j = 0;
		while(j < 50)
		{
			mlx_pixel_put(data->mlx, data->mlx_win, x + j, y + i, 0xFFFFFF);
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
				render_square(data, i * 50, j * 50);
			else if(data->map[j][i] == 'N')
			{
				render_player(data, 10);
				render_line(data, i * 50, j * 50, (i*50) + 50, (j*50) + 50);
			}

			i++;
		}
		j++;
	}
}