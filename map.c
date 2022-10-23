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

int check_xpm(char *xpm)
{
	int x;

	x = ft_strlen(xpm);
	if(xpm[0] == 'N' && xpm[1] == 'O')
	{
		if(xpm[x - 1] != 'm' || xpm[x - 2] != 'p' || xpm[x - 3] != 'x')
			return(0);
	}
	else if(xpm[0] == 'S' && xpm[1] == 'O')
	{
		if(xpm[x - 1] != 'm' || xpm[x - 2] != 'p' || xpm[x - 3] != 'x')
			return(0);
	}
	else if(xpm[0] == 'W' && xpm[1] == 'E')
	{
		if(xpm[x - 1] != 'm' || xpm[x - 2] != 'p' || xpm[x - 3] != 'x')
			return(0);
	}
	else if(xpm[0] == 'E' && xpm[1] == 'A')
	{
		if(xpm[x - 1] != 'm' || xpm[x - 2] != 'p' || xpm[x - 3] != 'x')
			return(0);
	}
	else
		return(0);
	return(1);
}

int set_file(t_cub *data, char *xpm, int j)
{
	int x;
	int y;
	char *p;
	p = malloc(ft_strlen(xpm) - 2);
	x = 3;
	y = 0;
	while(xpm[x])
	{
		p[y] = xpm[x];
		x++;
		y++;
	}
	p[y] = '\0';
	data->xpm_file[j] = ft_strdup(p);
	free(p);
	// y = open(data->xpm_file[j], O_RDONLY);
	// if(y == -1)
	// 	return (0);
	return (1);
}

int check_textures(t_cub *data)
{
	int j;
	j = 0;
	data->xpm_file = (char **)malloc(sizeof(char *) * 5);
	while(data->map[j] && j < 4)
	{
		if(!check_xpm(data->map[j]))
			return(0);
		if(!set_file(data, data->map[j], j))
			return(0);
		j++;
	}
	return(1);

}

int add_color(t_cub *data, int x, char c)
{
	char *p;
	int i;
	int j;
	int y = 0;
	i = 1;
	p = malloc(4);
	while(data->map[x][i])
	{
		j = 0;
		i++;
		while(data->map[x][i] != ',' && data->map[x][i])
		{
			if(!ft_isdigit(data->map[x][i]))
				return(0);
			p[j++] = data->map[x][i++];
		}
		p[j] = '\0';
		if(c == 'F')
			data->F_color[y] = ft_strdup(p);
		else
			data->C_color[y] = ft_strdup(p);
		y++;
		if(y > 3)
			return(0);
	}
	free(p);
	return(1);
}

int check_colors(t_cub *data)
{
	data->F_color = malloc(sizeof(char *) * 4);
	data->C_color = malloc(sizeof(char *) * 4);
	data->C_color[3] = NULL;
	data->F_color[3] = NULL;
	int i = 0;
	int x;
	if(data->map[4][i] == 'F' && data->map[5][i] == 'C')
	{
		if(!add_color(data, 4, 'F'))
			return(0);
		if(!add_color(data, 5, 'C'))
			return(0);
		x = 0;
		while(data->F_color[x] && data->C_color[x])
		{
			if(ft_atoi(data->F_color[x]) < 0 && ft_atoi(data->F_color[x]) > 255)
				return(0);
			if(ft_atoi(data->C_color[x]) < 0 && ft_atoi(data->C_color[x]) > 255)
				return(0);
			x++;
		}
		return(1);
	}
	return(0);
}


int	check_elements(t_cub *data)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if(!check_textures(data))
		return(0);
	if(!check_colors(data))
		return(0);
	// if(!check_map(data))
	// 	return(0);
	return (1);
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