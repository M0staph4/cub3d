/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:58:26 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/04 12:18:08 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int key, t_cub *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(data->mlx, data->img_3d.mlx_img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		ft_putendl_fd("EXIT", 1);
		exit(0);
	}
	if (key == KEY_W)
		move_up(data);
	else if (key == KEY_S)
		move_down(data);
	else if (key == KEY_D)
		move_right_left(data, key);
	else if (key == KEY_A)
		move_right_left(data, key);
	else if (key == KEY_RIGHT)
		rotate_right(data);
	else if (key == KEY_LEFT)
		rotate_left(data);
	return (0);
}

int	mouse(t_cub *data)
{
	mlx_destroy_image(data->mlx, data->img_3d.mlx_img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	ft_putendl_fd("EXIT", 1);
	exit(0);
	return (0);
}

void	window(t_cub *data)
{
	data->i_2d = 50;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1600, 900, "Cub3d!");
	data->img_3d.mlx_img = mlx_new_image(data->mlx, 1600, 900);
	data->img_3d.addr = mlx_get_data_addr(data->img_3d.mlx_img,
			&data->img_3d.bpp, &data->img_3d.line, &data->img_3d.endian);
	load_texture(data);
	player_pos(data);
	render_map(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_handler, data);
	mlx_hook(data->mlx_win, 17, 0L, mouse, data);
	mlx_loop(data->mlx);
}

int	check_extenssion(char *av)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(av);
	str = ft_substr(av, len - 4, len - 1);
	i = ft_strncmp(str, ".cub", 4);
	free(str);
	return (i);
}

int	main(int ac, char **av)
{
	int		fd;
	t_cub	data;

	if (ac == 2)
	{
		if (!check_extenssion(av[1]))
			fd = open(av[1], O_RDONLY);
		else
		{
			printf("File extenssion should be .cub");
			exit(0);
		}
		data.file = read_map(fd);
		if (check_elements(&data))
			window(&data);
		else
			printf("Map not valid\n");
	}
}
