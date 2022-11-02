#include "cub3d.h"

int	check_elements(t_cub *data)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!data->file)
		return (0);
	if (!check_all(data))
		return (0);
	if (!check_textures(data))
		return (0);
	if (!check_colors(data))
		return (0);
	if (!check_map(data))
		return (0);
	return (1);
}

int	check_new_line(char *map, char *line)
{
	int	i;
	int	x;

	x = 0;
	i = ft_strlen(map) - 2;
	if (line[0] == '\n')
	{
		while (i && map[i] == ' ')
			i--;
		x = i;
		while (i && map[i] != '\n')
			i--;
		i++;
		while (map[i] && map[i] == ' ')
			i++;
		if (map[x] == '1' && map[i] == '1')
			return (0);
	}
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
		if (!check_new_line(mapp, map))
			return (NULL);
		mapp = ft_strjoin(mapp, map);
		free(map);
		map = get_next_line(i);
		y++;
	}
	p = ft_split(mapp, '\n');
	if (ft_strlen(mapp) <= 2)
		return (NULL);
	if (mapp[ft_strlen(mapp) - 1] == '\n')
		return (NULL);
	free(mapp);
	return (p);
}
