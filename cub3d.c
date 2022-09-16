#include "cub3d.h"

char	**read_map(int i)
{
	char	*map;
	char	*mapp;
	char	**p;
	int		y;

	y = 0;
	mapp = ft_strdup("");
	map = get_next_line(i);
	while (map)
	{
		mapp = ft_strjoin(mapp, map);
		free(map);
		map = get_next_line(i);
		y++;
	}
	p = ft_split(mapp, '\n');
	free(mapp);
	return (p);
}

int key_handler(int key, t_cub *data)
{
	if(key == KEY_UP)
		data->walk = 1;
	else if(key == KEY_DOWN)
		data->walk = -1;
	else if(key == KEY_RIGHT)
		data->side = 1;
	else if(key == KEY_LEFT)
		data->side = -1;
	data->rotation_angle += data->side * data->rotation_speed;
	return (0);	

}

void player_pos(t_cub *data)
{
	int i;
	int j;
	j = 0;
	data->side = 0;
	data->walk = 0;
	data->move_speed = 2.0;
	data->rotation_angle = PI / 2;
	data->rotation_speed = 2 * (PI / 180);
	while(data->map[j])
	{
		i = 0;
		while(data->map[j][i])
		{
			if(data->map[j][i] == 'N')
			{
				data->xpos = i;
				data->ypos = j;				
			}
			i++;
		}
		j++;
	}

}

void	window(t_cub *data)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(data->map[0]);
	while (data->map[j])
		j++;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, i * 50, j * 50, "Cub3d!");
	player_pos(data);
	render_map(data);
	mlx_key_hook(data->mlx_win, key_handler, data);
	// mlx_hook(mlx_win, 17, 0L, mouse, mlx);
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
		window(&data);
	}
}