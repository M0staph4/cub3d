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

int set_xmp(char *xpm, t_cub *data, int x)
{
	int i;
	int y;
	y = 0;
	i = 0;
	while(xpm[i] && xpm[i] != '.')
	{
		if((xpm[i] >= 'A' && xpm[i + 1] <= 'W') || xpm[i] == ' ')
			i++;
		if(xpm[i] != '.')
			i++;
	}
	y = ft_strlen(xpm) - 1;
	if(i >= y)
		return(7);
	while(xpm[y] == ' ')
		y--;
	if(!y || data->xpm_file[x])
		return(7);
	data->xpm_file[x] = ft_substr(xpm, i, y - i + 1);
	return(1);
}

int set_color(t_cub *data, char *color, char c)
{
	int i;
	int x;
	char *nb;

	i = 0;
	x = ft_strlen(color) - 1;
	while(!ft_isdigit(color[i]) && color[i])
		i++;
	if(i >= x || color[i - 1] != ' ')
		return(7);
	while(color[x] == ' ')
		x--;
	nb = ft_substr(color, i, x - i + 1);
	if(!check_nb(nb))
		return(7);
	nb = check_nb(nb);
	if(c == 'F' && !data->F_color)
		data->F_color = ft_split(nb, ',');
	else if(c == 'C' && !data->C_color)
		data->C_color = ft_split(nb, ',');
	return(1);
}

int check_all(t_cub *data)
{
	int i;
	int j;
	int x;

	x = -1; 
	i = 0;
	j = 0;
	data->xpm_file = malloc(sizeof(char *) * 5);
	data->xpm_file[4] = NULL;
	while(data->xpm_file[++x])
		data->xpm_file[x] = NULL;
	x = 0;
	data->F_color = malloc(sizeof(char *) * 4);
	data->C_color = malloc(sizeof(char *) * 4);
	data->C_color = NULL;
	data->F_color = NULL;
	while(data->file[j])
	{
		while(data->file[j][i] == ' ')
			i++;
		if(data->file[j][i] == 'N' && data->file[j][i + 1] == 'O' && data->file[j][i + 2] == ' ')
			x += set_xmp(data->file[j], data, 0);
		else if(data->file[j][i] == 'S' && data->file[j][i + 1] == 'O' && data->file[j][i + 2] == ' ')
			x += set_xmp(data->file[j], data, 1);
		else if(data->file[j][i] == 'W' && data->file[j][i + 1] == 'E' && data->file[j][i + 2] == ' ')
			x += set_xmp(data->file[j], data, 2);
		else if(data->file[j][i] == 'E' && data->file[j][i + 1] == 'A' && data->file[j][i + 2] == ' ')
			x += set_xmp(data->file[j], data, 3);
		else if(data->file[j][i] == 'F' && data->file[j][i + 1] == ' ')
			x += set_color(data, data->file[j], 'F');
		else if(data->file[j][i] == 'C' && data->file[j][i + 1] == ' ')
			x += set_color(data, data->file[j], 'C');
		i = 0;
		j++;
	}
	if(x != 6)
		return(0);
	return(1);
}

int check_zero(char **map, int j, int i)
{
	if(ft_strlen(map[j + 1]) <= (size_t)i || ft_strlen(map[j - 1]) <= (size_t)i)
		return(0);
	if(map[j][i + 1] == ' ' || map[j][i - 1] == ' ')
		return(0);
	if(map[j - 1][i] == ' ' || map[j + 1][i] == ' ')
		return(0);
	return(1);
}

int check_spaces(char **map)
{
	int i;
	int j;
	j = 0;
	while(map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if(map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'W'
				|| map[j][i] == 'S' || map[j][i] == 'E')
			{
				if(!check_zero(map, j, i))
					return(0);
			}
			i++;
		}
		j++;
	}
	return(1);
}

int is_close(char **map)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while(map[0][i] && (map[0][i] == '1' || map[0][i] == ' '))
		i++;
	if((size_t)i != ft_strlen(map[0]))
		return(0);
	i = 0;
	while(map[++j])
	{
		while(map[j][i] == ' ')
			i++;
		if(map[j][i] != '1' && map[j][ft_strlen(map[j]) - 1] != '1')
			return(0);
		i = 0;
	}
	while(map[j - 1][i] && (map[j - 1][i] == '1' || map[j - 1][i] == ' '))
		i++;
	if((size_t)i != ft_strlen(map[j - 1]))
		return(0);
	if(!check_spaces(map))
		return(0);
	return(1);
}

int check_walls(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(!check_player(map))
		return(0);
	if(!is_close(map))
		return(0);
	return(1);
}

int check_map(t_cub *data)
{
	int i;
	int x;
	i = 0;
	x = 0;
	while(data->file[i])
		i++;
	data->map = malloc(sizeof(char *) * (i - 5));
	data->map[i - 6] = NULL;
	i = 6;
	while(data->file[i])
		data->map[x++] = ft_strdup(data->file[i++]);
	if(!check_walls(data->map))
		return(0);
	return(1);
}

int	check_elements(t_cub *data)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if(!check_all(data))
		return (0);
	if(!check_textures(data))
		return (0);
	if(!check_colors(data))
		return (0);
	if(!check_map(data))
		return(0);
	return (1);
}

int check_new_line(char *map, char *line)
{
	int i;
	int x;
	x = 0;
	i = ft_strlen(map) - 2;
	if(line[0] == '\n')
	{
		while(i && map[i] == ' ')
			i--;
		x = i;
		while(i && map[i] != '\n')
			i--;
		i++;
		while(map[i] && map[i] == ' ')
			i++;
		if(map[x] == '1' && map[i] == '1')
			return(0);
	}
	return(1);
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
		if(!check_new_line(mapp, map))
			return(NULL);
		mapp = ft_strjoin(mapp, map);
		free(map);
		map = get_next_line(i);
		y++;
	}
	p = ft_split(mapp, '\n');
	if(ft_strlen(mapp) <= 2)
		return(NULL);
	if(mapp[ft_strlen(mapp) - 1] == '\n')
		return(NULL);
	free(mapp);
	return (p);
}