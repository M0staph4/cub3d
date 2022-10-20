#include "cub3d.h"

int check_wall_collision(t_cub *data)
{
	int i;
	int j;
	
	i = data->xpos + cos(data->rotation_angle) * data->move_step;
	j = data->ypos + sin(data->rotation_angle) * data->move_step;
	if(data->map[j / data->i_2D][i / data->i_2D] == '1')
		return(0);
	return(1);
}

int check_wall_collision_2D(t_cub *data)
{
	int i;
	int j;
	
	i = data->xpos + cos(data->rotation_angle) * data->move_step;
	j = data->ypos + sin(data->rotation_angle) * data->move_step;
	if(data->map[j / data->i_2D][i / data->i_2D] == '1')
		return(0);
	return(1);
}
int	check_wall(char **map)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (map[i][0] != '1' || map[i][j - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_elements(char **map)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (map[i])
	{
		x = 0;
		while (map[i][x])
		{
			if (map[i][x] != '1' && map[i][x] != '0' && map[i][x] != 'N' && map[i][x] != ' '
				&& map[i][x] != 'S' && map[i][x] != 'E' && map[i][x] != 'W')
				return (1);
			x++;
		}
		i++;
	}
	return (0);
}

void	check_map(char **map)
{
	if (check_elements(map) || check_wall(map))
	{
		write(2, "not valid\n", 11);
		exit(0);
	}
}

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