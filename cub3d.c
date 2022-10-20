#include "cub3d.h"

int key_handler(int key, t_cub *data)
{
	if (key == KEY_UP)
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
	else if (key == KEY_DOWN)
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
	else if (key == KEY_RIGHT)
	{
		data->side = 1;
		data->rotation_angle += data->side * data->rotation_speed;
		render_map(data);
	}
	else if (key == KEY_LEFT)
	{
		data->side = -1;
		data->rotation_angle += data->side * data->rotation_speed;
		render_map(data);
	}
	return (0);	
}

double check_direction(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if (data->map[j][i] == 'N')
				return (PI / 2);
			else if (data->map[j][i] == 'W')
				return (PI);
			else if (data->map[j][i] == 'S')
				return (PI3);
			else if ( data->map[j][i] == 'E')
				return (0);
			i++;
		}
		j++;
	}
	return (0);
}

void player_init(t_cub *data)
{
	data->side = 0;
	data->walk = 0;
	data->move_speed = 3;
	data->rotation_angle = check_direction(data);
	data->rotation_speed = 3 * (PI / 180);
}

void player_pos_2D(t_cub *data)
{
	int i;
	int j;
	j = 0;
	player_init(data);
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N' || data->map[j][i] == 'E'
				|| data->map[j][i] == 'S' || data->map[j][i] == 'W')
			{
				data->map[j][i] = '0';
				data->xpos = i * data->i_2D;
				data->ypos = j * data->i_2D;				
			}
			i++;
		}
		j++;
	}
}

void	pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line + x * (data->bpp / 8));
	*(int*)dst = color;
}

int	get_pixel_color(t_texture *tex)
{
	// int		color;
	// color = (int)tex->img.addr[tex->texY * tex->img.line / (tex->img.bpp / 8) + tex->texX];
	return ((int)tex->img.addr + (tex->texY * tex->img.line + tex->texX * (tex->img.bpp / 8)));
}


void	window(t_cub *data)
{
	int		i;
	int		j;
	int		x;
	int		y;
	j = 0;
	i = ft_strlen(data->map[0]);
	char	*path = "bluestone.xpm";
	while (data->map[j])
		j++;
	data->i_2D = 50;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1080, 720, "Cub3d!");
	data->img_3D.mlx_img = mlx_new_image(data->mlx, 1080, 720);
	data->img_3D.addr = mlx_get_data_addr(data->img_3D.mlx_img, &data->img_3D.bpp, &data->img_3D.line, &data->img_3D.endian);
	data->tex.texture = mlx_xpm_file_to_image(data->mlx, path, &x, &y);
	data->tex.img.addr =  mlx_get_data_addr(data->tex.texture, &data->tex.img.bpp, &data->tex.img.line, &data->tex.img.endian);
	player_pos_2D(data);
	render_map(data);
	mlx_hook(data->mlx_win, 2, 1L<<0,  key_handler, data);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	int fd;
	t_cub data;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		data.map = read_map(fd);
		check_map(data.map);
		window(&data);
	}
}