#include "cub3d.h"

void    move_up(t_cub *data)
{
    data->walk = 1;
	data->move_step = data->walk * data->move_speed;
	if (check_wall_collision(data))
	{
		data->xpos += cos(data->rotation_angle) * data->move_step;
		data->ypos += sin(data->rotation_angle) * data->move_step;
		render_map(data);
	}
}

void    move_down(t_cub *data)
{
    data->walk = -1;
    data->move_step = data->walk * data->move_speed;
    if (check_wall_collision(data))
    {
    	data->xpos += cos(data->rotation_angle) * data->move_step;
    	data->ypos += sin(data->rotation_angle) * data->move_step;
    	render_map(data);
    }
}

void    rotate_left(t_cub *data)
{
	data->side = -1;
	data->rotation_angle += data->side * data->rotation_speed;
	render_map(data);
}

void    rotate_right(t_cub *data)
{
    data->side = 1;
	data->rotation_angle += data->side * data->rotation_speed;
	render_map(data);
}

void    move_left(t_cub *data)
{
    data->walk = -1;
    data->move_step = data->walk * data->move_speed;
    if (check_wall_collision(data))
    {
    		data->xpos += cos(data->rotation_angle + 1.57) * data->move_step;
			data->ypos += sin(data->rotation_angle  + 1.57) * data->move_step;
    	render_map(data);
    }
}

void    move_right(t_cub *data)
{
    data->walk = 1;
    data->move_step = data->walk * data->move_speed;
    if (check_wall_collision(data))
    {
    		data->xpos += cos(data->rotation_angle + 1.57) * data->move_step;
			data->ypos += sin(data->rotation_angle  + 1.57) * data->move_step;
    	render_map(data);
    }
}

int key_handler(int key, t_cub *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(data->mlx, data->img_3D.mlx_img);
		exit(0);
	}
	if (key == KEY_UP || key == KEY_W)
        move_up(data);
	else if (key == KEY_DOWN || key == KEY_S)
		move_down(data);
	else if (key == KEY_D)
		move_right(data);
	else if (key == KEY_A)
		move_left(data);
	else if (key == KEY_RIGHT)
		rotate_right(data);
	else if (key == KEY_LEFT)
		rotate_left(data);
	else if (key == KEY_E)
		render_map(data);
	return (0);	
}