#include "cub3d.h"

int direction(t_cub *data)
{
    if(data->map[((int)data->pixelY + 1) / data->i_2D][(int)data->pixelX / data->i_2D] == '0')
        data->tex.texPos = 1;
    if(data->map[(int)data->pixelY / data->i_2D][((int)data->pixelX + 1) / data->i_2D] == '0')
        data->tex.texPos = 2;    
    if(data->map[((int)data->pixelY - 1) / data->i_2D][(int)data->pixelX / data->i_2D] == '0')
        data->tex.texPos = 3;
    if(data->map[(int)data->pixelY / data->i_2D][((int)data->pixelX - 1) / data->i_2D] == '0')
        data->tex.texPos = 4;
    return(data->tex.texPos);
}

void    wall_projection(t_cub *data, int i)
{
    int j;

    j = 0;
    while(j < WINDOW_HEIGHT)
    {
        if (direction(data) == 1 || direction(data) == 3)
            data->tex.texX = fmod(data->pixelX / 50, 1) * 50;
        if (direction(data) == 2 || direction(data) == 4)
            data->tex.texX = fmod(data->pixelY / 50, 1) * 50;
        data->tex.texY = ((j - ((WINDOW_HEIGHT - data->wall) / 2)) * 50) / data->wall;
        if (j < (WINDOW_HEIGHT - data->wall) / 2)
            pixel_put(&data->img_3D, i, j, 0xF2F7FA);
        else if (j < ((WINDOW_HEIGHT - data->wall) / 2) + data->wall)
            pixel_put(&data->img_3D, i, j, get_pixel_color(&data->tex));
        else
            pixel_put(&data->img_3D, i, j, 0x536878);
        j++;
    }
}

void    raycasting(t_cub *data)
{
    int     i;
    double  ray_angle;
    double  deltaX;
    double  deltaY;

    i = 0;
    ray_angle = -32;
    while (i < WINDOW_WIDTH )
    {
        if(ray_angle <= 32)
        {
            deltaX = (data->xpos + cos(data->rotation_angle + ray_angle) * 1000) - data->xpos;
            deltaY = (data->ypos +  sin(data->rotation_angle + ray_angle) * 1000) - data->ypos;
            render_line(data, deltaX, deltaY, data->rotation_angle + ray_angle, 1);
        }
        wall_projection(data, i);
        i++;
        ray_angle+= (64 * (PI / 180)) / WINDOW_WIDTH;
    }
}
