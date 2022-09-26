#include "cub3d.h"

int direction(t_cub *data)
{
    int k;

    if(data->map[(((int)data->pixelY + 1) / data->i_2D)][((int)data->pixelX / data->i_2D)] == '0')
        k = 1;
    if(data->map[((int)data->pixelY / data->i_2D)][(((int)data->pixelX + 1) / data->i_2D)] == '0')
        k = 2;
    if(data->map[(((int)data->pixelY - 1) / data->i_2D)][((int)data->pixelX / data->i_2D)] == '0')
        k = 3;
    if(data->map[((int)data->pixelY / data->i_2D)][(((int)data->pixelX - 1) / data->i_2D)] == '0')
        k = 4;
    return(k);
}

void    raycasting(t_cub *data)
{
    int i = 0;
    int j;
    double x  = - PI / 6;
    double l = data->rotation_angle;
    // double step = 1.0 * data->i_2D/ data->wall;
    // double tex;
    // double wall_x;
    while (i < WINDOW_WIDTH)
    {
        // if (data->side == 0)
        //     wall_x = data->ypos + data->player_dis * data->pixelY;
        // else
        //     wall_x = data->xpos + data->player_dis * data->pixelX;
        // data->tex.texX = i / 64;
        j = 0;
        if ( x < PI / 6 && x != 0)
            render_line(data,(data->xpos + cos(l + x) * 1000) - data->xpos,(data->ypos + sin(l + x) * 1000) - data->ypos,  0x40E0D0);
        while(j < WINDOW_HEIGHT)
        {
            if (j < (WINDOW_HEIGHT - data->wall)  / 2)
                pixel_put(&data->img_3D, i, j, 0xFFFFFF);
            else if (j < ((WINDOW_HEIGHT - data->wall) / 2) + data->wall)
            {
                // data->tex.texY = (j - (((WINDOW_HEIGHT - data->wall) / 2))) / 64;
                //     data->tex.texY =tex;
                //     tex += step;
                if (direction(data) == 1)
                    pixel_put(&data->img_3D, i, j, 0xE0AC69);
                if (direction(data) == 2)
                    pixel_put(&data->img_3D, i, j, 0xE0AC69);
                if (direction(data) == 3)
                    pixel_put(&data->img_3D, i, j, 0xF1C27D);
                if (direction(data) == 4)
                    pixel_put(&data->img_3D, i, j, 0xFFDBAC);
            }
            else
                pixel_put(&data->img_3D, i, j, 0x8D5524);
            j++;
        }
        i++;
        x+= 0.001;
    }
}
