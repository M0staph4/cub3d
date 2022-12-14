/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:05:56 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/04 12:28:29 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_xmp(char *xpm, t_cub *data, int x)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (xpm[i] && xpm[i] != '.')
	{
		if ((xpm[i] >= 'A' && xpm[i + 1] <= 'W') || xpm[i] == ' ')
			i++;
		if (xpm[i] != '.')
			i++;
	}
	y = ft_strlen(xpm) - 1;
	if (i >= y)
		return (7);
	while (xpm[y] == ' ')
		y--;
	if (!y)
		return (7);
	data->xpm_file[x] = ft_substr(xpm, i, y - i + 1);
	return (1);
}

int	set_color(t_cub *data, char *color, char c)
{
	int		i;
	int		x;
	char	*nb;

	i = 0;
	x = ft_strlen(color) - 1;
	while (!ft_isdigit(color[i]) && color[i])
		i++;
	if (i >= x || (color[i - 1] != ' ' && color[i - 1] != '\t'))
		return (7);
	while (color[x] == ' ' || color[x] == '\t')
		x--;
	nb = ft_substr(color, i, x - i + 1);
	nb = check_nb(nb, 0, 0);
	if (!nb)
		return (7);
	if (c == 'F' && !data->f_color)
		data->f_color = ft_split(nb, ',');
	else if (c == 'C' && !data->c_color)
		data->c_color = ft_split(nb, ',');
	free(nb);
	return (1);
}

int	init_xpm(char *file, int i, t_cub *data)
{
	int	x;

	x = 0;
	if (file[i] == 'N' && file[i + 1] == 'O' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 0);
	else if (file[i] == 'S' && file[i + 1] == 'O' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 1);
	else if (file[i] == 'W' && file[i + 1] == 'E' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 2);
	else if (file[i] == 'E' && file[i + 1] == 'A' && (file[i + 2] == ' '
			|| file[i + 2] == '\t'))
		x += set_xmp(file, data, 3);
	return (x);
}

int	init_map(char *file, t_cub *data)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (file[i] == ' ' || file[i] == '\t')
		i++;
	if (file[i] == 'N' || file[i] == 'S'
		|| file[i] == 'W' || file[i] == 'E')
		x += init_xpm(file, i, data);
	else if (file[i] == 'F' && (file[i + 1] == ' '
			|| file[i + 1] == '\t'))
		x += set_color(data, file, 'F');
	else if (file[i] == 'C' && (file[i + 1] == ' '
			|| file[i + 1] == '\t'))
		x += set_color(data, file, 'C');
	return (x);
}

int	check_all(t_cub *data)
{
	int	i;
	int	j;
	int	x;

	x = -1;
	i = 0;
	j = -1;
	data->xpm_file = malloc(sizeof(char *) * 5);
	data->xpm_file[4] = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	while (data->xpm_file[++x])
		data->xpm_file[x] = NULL;
	x = 0;
	while (data->file[++j])
		x += init_map(data->file[j], data);
	if (x != 6)
		return (0);
	return (1);
}
