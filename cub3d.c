#include "cub3d.h"

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
	data->move_speed = 20;
	data->rotation_angle = check_direction(data);
	data->rotation_speed = 6 * (PI / 180);
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

int	mouse(t_cub *data)
{
	mlx_destroy_image(data->mlx, data->img_3D.mlx_img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
	return (0);
}

void	window(t_cub *data)
{
	int		i;
	int		j;
	
	j = 0;
	i = ft_strlen(data->map[0]);
	data->i_2D = 50;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d!");
	data->img_3D.mlx_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img_3D.addr = mlx_get_data_addr(data->img_3D.mlx_img, &data->img_3D.bpp, &data->img_3D.line, &data->img_3D.endian);
	load_texture(data);
	player_pos_2D(data);
	render_map(data);
	mlx_hook(data->mlx_win, 2, 1L<<0,  key_handler, data);
	mlx_hook(data->mlx_win, 17, 0L, mouse, data);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	int fd;
	t_cub data;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		data.file = read_map(fd);
		if(data.file && check_elements(&data))
			window(&data);
		// printf("rigola\n");
	}
}