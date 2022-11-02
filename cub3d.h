/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoutawa <mmoutawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:09:03 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/11/02 19:54:19 by mmoutawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include "inc/libft/libft.h"
# include "inc/gnl/get_next_line.h"
# include "mlx_keys.h"
# define PI 3.1415926535
# define PI2 1.5708
# define PI3 4.71239
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

typedef struct s_img{
	void	*mlx_img;
	char	*addr;
	int		endian;
	int		bpp;
	int		line;
}	t_img;

typedef struct s_tex_img{
	void			*texture;
	unsigned int	*addr;
	int				endian;
	int				bpp;
	int				line;
}	t_tex_img;

typedef struct s_texture{
	int			tex_x;
	int			tex_y;
	double		step;
	double		texpos;
	t_tex_img	img[4];
}	t_texture;

typedef struct s_rgb{
	int r_c;
	int g_c;
	int b_c;
	int r_f;
	int g_f;
	int b_f;
}t_rgb;

typedef struct s_cub{
	void		*mlx;
	void		*mlx_win;
	char		**map;
	double		xpos;
	double		ypos;
	double		deltax;
	double		deltay;
	double		side;
	double		walk;
	double		rotation_angle;
	double		move_speed;
	double		rotation_speed;
	double		move_step;
	double		player_dis;
	double		projection_plane;
	double		wall;
	int			i_2d;
	double		pixelx;
	double		pixely;
	char		**file;
	char		**xpm_file;
	char		**f_color;
	char		**c_color;
	t_rgb		colors;
	t_img		img_3d;
	t_texture	tex;
}	t_cub;

void	render_line(t_cub *data, double angle, int ray);
void	render_player(t_cub *data, int r, int x);
void	render_square(t_cub *data, int x, int y, int color, int xx);
void	render_map(t_cub *data);
char	**read_map(int i);
int		check_elements(t_cub *data);
int		check_map(t_cub *data);
int		check_wall_collision(t_cub *data);
void	pixel_put(t_img *img, int x, int y, int color);
void	raycasting(t_cub *data);
void	player_pos(t_cub *data);
int		check_wall_collision_2D(t_cub *data);
int		get_pixel_color(t_texture *tex);
int		key_handler(int key, t_cub *data);
void	move_right_left(t_cub *data, int key);
void	rotate_right(t_cub *data);
void	rotate_left(t_cub *data);
void	move_down(t_cub *data);
void	move_up(t_cub *data);
int		hitwall(t_cub *data, double x, double y);
void	load_texture(t_cub *data);
char	*check_nb(char *color);
int		check_textures(t_cub *data);
int		check_player(char **map);
int		check_colors(t_cub *data);
double	player_distance(t_cub *data, double angle);
double	projection_plane(void);
double	wall_height(t_cub *data);
int		init_map(char *file, t_cub *data);
int		check_player(char **map);
int		check_walls(char **map);
int		check_all(t_cub *data);

#endif