#include "cub3d.h"

int its_ok(char *color, int i)
{
	while(color[i] == ' ' || color[i] == '\t')
	{
		if((color[i] == ' ' || color[i] == '\t') && ft_isdigit(color[i + 1]))
			return(-1);
		i++;
	}
	return(i - 1);
}

char *check_nb(char *color)
{
	int i;
	int x;
	int j;
	char *nb;

	nb = calloc(1,12);
	x = 0;
	j = 0;
	i = -1;
	while(color[++i])
	{
		if(color[i] == ',' && color[i + 1] != ',' && color[i - 1] != ',')
			x++;
		if(color[i] != ' ' && color[i] != '\t')
			nb[j++] = color[i];
		if(color[i] == ' ' && ft_isdigit(color[i - 1]))
		{
			if(0 > its_ok(color, i))
				return(NULL);
			i = its_ok(color, i);
		}
	}
	if(x != 2)
		return(NULL);
	return(nb);
}
int check_textures(t_cub *data)
{
	int i;
	int x;
	i = 0;
	x = 0;
	while(data->xpm_file[i])
	{
		x = ft_strlen(data->xpm_file[i]) - 1;
		if(data->xpm_file[i][x] != 'm' 
			|| data->xpm_file[i][x - 1] != 'p' 
			|| data->xpm_file[i][x - 2] != 'x' 
			|| data->xpm_file[i][x - 3] != '.')
		return(0);
		if(open(data->xpm_file[i], O_RDONLY) < 0)
			return(0);
		i++;
	}
	return (1);
}

int check_player(char **map)
{
	int i;
	int j;
	int x;

	x = 0;
	i = -1;
	j = -1;
	while(map[++j])
	{
		i = -1;
		while(map[j][++i])
		{
			if(map[j][i] != '1' && map[j][i] != ' ' && map[j][i] != '0')
			{
				x++;
				if(map[j][i] != 'N' && map[j][i] != 'S' 
					&& map[j][i] != 'W' && map[j][i] != 'E')
					return(0);
			}
		}
	}
	if(x != 1)
		return(0);
	return(1);
}

int check_colors(t_cub *data)
{
	int i;
	int j =0;
	i = 0;
	if(!data->C_color || !data->F_color)
		return (0);
	while(data->C_color[j] && data->F_color[i])
	{
		if(ft_strlen(data->C_color[j]) > 3)
			return(0);
		if(ft_strlen(data->F_color[i]) > 3)
			return(0);
		if(ft_atoi(data->C_color[j]) > 255)
			return(0);
		if(ft_atoi(data->F_color[i]) > 255)
			return(0);
		i++;
		j++;
	}
	return (1);

}