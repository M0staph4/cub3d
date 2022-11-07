/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:05:53 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/04 00:15:25 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	its_ok(char *color, int i)
{
	while (color[i] == ' ' || color[i] == '\t')
	{
		if ((color[i] == ' ' || color[i] == '\t') && ft_isdigit(color[i + 1]))
			return (-1);
		i++;
	}
	return (i - 1);
}

char	*check_nb(char *color, int x, int j)
{
	int		i;
	char	*nb;

	nb = calloc(1, 12);
	i = -1;
	while (color[++i])
	{
		if (color[i] == ',' && color[i + 1] != ',' && color[i - 1] != ',')
			x++;
		if (color[i] != ' ' && color[i] != '\t')
			nb[j++] = color[i];
		if ((color[i] == ' ' || color[i] == '\t') && ft_isdigit(color[i - 1]))
		{
			if (0 > its_ok(color, i))
				return (NULL);
			i = its_ok(color, i);
		}
	}
	if (x != 2)
		return (NULL);
	free(color);
	return (nb);
}

int	check_textures(t_cub *data)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (data->xpm_file[i])
	{
		x = ft_strlen(data->xpm_file[i]) - 1;
		if (data->xpm_file[i][x] != 'm'
			|| data->xpm_file[i][x - 1] != 'p'
			|| data->xpm_file[i][x - 2] != 'x'
			|| data->xpm_file[i][x - 3] != '.')
			return (0);
		if (open(data->xpm_file[i], O_RDONLY) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	rgb(t_cub *data)
{
	int	i;

	i = 0;
	data->colors.r_c = ft_atoi(data->c_color[0]);
	data->colors.g_c = ft_atoi(data->c_color[1]);
	data->colors.b_c = ft_atoi(data->c_color[2]);
	data->colors.r_f = ft_atoi(data->f_color[0]);
	data->colors.g_f = ft_atoi(data->f_color[1]);
	data->colors.b_f = ft_atoi(data->f_color[2]);
}

int	check_colors(t_cub *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!data->c_color || !data->f_color)
		return (0);
	while (data->c_color[j] && data->f_color[i])
	{
		if (ft_strlen(data->c_color[j]) > 3)
			return (0);
		if (ft_strlen(data->f_color[i]) > 3)
			return (0);
		if (ft_atoi(data->c_color[j]) > 255)
			return (0);
		if (ft_atoi(data->f_color[i]) > 255)
			return (0);
		i++;
		j++;
	}
	rgb(data);
	return (1);
}
