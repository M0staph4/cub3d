#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mlx.h>
#include "inc/libft/libft.h"
#include "inc/gnl/get_next_line.h"
#include "mlx_keys.h"

#define PI 3.1415926535
#define PI2 1.5708
#define PI3 4.71239
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define FOV 64 * (PI / 2)

typedef struct   s_img{
    void    *mlx_img;
    char    *addr;
    int     endian;
    int     bpp;
    int     line;
}   t_img;

typedef struct   s_tex_img{
    void			*texture;
    unsigned int    *addr;
    int				endian;
    int				bpp;
    int				line;
}   t_tex_img;

typedef struct  s_texture{
    int     texX;
    int     texY;
    double  step;
    double  texPos;
    t_tex_img   img[4];
}   t_texture;

typedef struct s_cub{
    void	*mlx;
    void	*mlx_win;
    char	**map;
    double  xpos;
    double  ypos;
	double	side;
	double	walk;
    double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
    double  move_step;
    double  player_dis;
    double  projection_plane;
    double  wall;
    int     i_2D;
    double  pixelX;
    double  pixelY;
    char **file;
    char    **xpm_file;
    char    **F_color;
    char    **C_color;
    t_img   img_3D;
    t_texture tex;
}   t_cub;


void	render_line(t_cub *data, double deltaX, double deltaY, double x, int c);
void	render_player(t_cub *data, int r);
void	render_square(t_cub *data, int x, int y, int color);
void	render_map(t_cub *data);
char	**read_map(int i);
int     check_elements(t_cub *data);
int 	check_map(t_cub *data);
int     check_wall_collision(t_cub *data);
void	pixel_put(t_img *img, int x, int y, int color);
void    raycasting(t_cub *data);
void	player_pos(t_cub *data);
int		check_wall_collision_2D(t_cub *data);
int		get_pixel_color(t_texture *tex);
int     key_handler(int key, t_cub *data);
void	load_texture(t_cub *data);
char *check_nb(char *color);
int check_textures(t_cub *data);
int check_player(char **map);
int check_colors(t_cub *data);

#endif