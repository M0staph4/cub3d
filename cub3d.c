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
	int i = 0;
	if((key == KEY_UP && data->map[data->ypos / 50][data->xpos / 50] != '1') || i)
	{
		data->walk = 1;
		data->move_step = data->walk * data->move_speed;
		data->xpos += cos(data->rotation_angle) * data->move_step;
		data->ypos += sin(data->rotation_angle) * data->move_step;
		if(data->map[data->ypos / 50][data->xpos / 50] != '1')
			i = 1;
		render_map(data);
	}
	else if(key == KEY_DOWN)
	{
		data->walk = -1;
		data->move_step = data->walk * data->move_speed;
		data->xpos += cos(data->rotation_angle) * data->move_step;
		data->ypos += sin(data->rotation_angle) * data->move_step;
		render_map(data);
	}
	else if(key == KEY_RIGHT)
	{
		data->side = 1;
		data->rotation_angle += data->side * data->rotation_speed;
		render_map(data);
	}
	else if(key == KEY_LEFT)
	{
		data->side = -1;
		data->rotation_angle += data->side * data->rotation_speed;
		render_map(data);
	}
	return (0);	
}

void player_init(t_cub *data)
{
	data->side = 0;
	data->walk = 0;
	data->move_speed = 4;
	data->rotation_angle = PI / 2;
	data->rotation_speed = 3 * (PI / 180);
}

void player_pos(t_cub *data)
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
			if (data->map[j][i] == 'N')
			{
				data->map[j][i] = '0';
				data->xpos = i * 50;
				data->ypos = j * 50;				
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
	//void *image;

	j = 0;
	i = ft_strlen(data->map[0]);
	while (data->map[j])
		j++;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, i * 50, j * 50, "Cub3d!");
	//image = mlx_new_image(data->mlx, 640, 360);
	player_pos(data);
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
		window(&data);
	}
}