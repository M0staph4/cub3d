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
#define PI2 1.5708 //pi/2
#define PI3 4.71239 //3pi/2
#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1200
typedef struct   s_img{
    void    *mlx_img;
    char    *addr;
    int     endian;
    int     bpp;
    int     line;
}   t_img;

double g_i;
double g_j;
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
    char    direction;
    double wall_size;
    double wall_height;
    void *img_3d;
    double dis;
    double wall;
    t_img   img;
}   t_cub;


void	render_line(t_cub *data, double deltaX, double deltaY, int color);
void	render_player(t_cub *data, int r);
void	render_square(t_cub *data, int x, int y, int color);
void	render_map(t_cub *data);
char	**read_map(int i);
int     check_elements(char **map);
void	check_map(char **map);
int     check_wall_collision(t_cub *data);
void	pixel_put(t_img *img, int x, int y, int color);


#endif