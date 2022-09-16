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
typedef struct s_cub{
    void	*mlx;
    void	*mlx_win;
    char	**map;
    int     xpos;
    int     ypos;
	int		side;
	int		walk;
    double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}   t_cub;

void	render_line(t_cub *data, int beginX, int beginY, int endX, int endY);
void	render_player(t_cub *data, int r);
void	render_square(t_cub *data, int x, int y);
void	render_map(t_cub *data);

#endif