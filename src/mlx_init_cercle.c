/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:10:25 by roberodr          #+#    #+#             */
/*   Updated: 2023/04/20 15:36:42 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct s_circle{
	int eje_x;
	int eje_y;
	int radio;
	
}	t_circle;

typedef struct  s_vars {
   	void	*mlx;
	void	*mlx_win;
	t_circle *circle; 
	t_data *data;
	
}               t_vars;

int     key_hook_close(int keycode, t_vars *vars)
{
    if (keycode == 53)  // tecla Esc
    {
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit(0);
    }
    return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_putcircle( t_circle  *circle, t_data *img)
{
    int i;
    float theta;
	for (i = 0; i <= 360; i++) 
	{
        theta = i * M_PI / 180.0;
        int cx = circle->eje_x + circle->radio * cos(theta);
        int cy = circle->eje_y + circle->radio * sin(theta);
		my_mlx_pixel_put(img, cx, cy, 0x00FFF00);
    }
}
int key_hook(int keycode, t_vars *vars)
{
	 
	if (keycode == 69) // tecla +
		{
			if(vars->circle->radio > 350)
				return(0);
			mlx_destroy_image(vars->mlx, vars->data->img);
			vars->circle->radio = vars->circle->radio  + 10;
			vars->data->img = mlx_new_image(vars->mlx, 800, 600);
			ft_putcircle(vars->circle, vars->data);
			mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
			
		}
	if (keycode == 78) //tecla -
	{
		if(vars->circle->radio < 1)
			return(0); 
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->circle->radio = vars->circle->radio  - 10;
		vars->data->img = mlx_new_image(vars->mlx, 800, 600);
		ft_putcircle(vars->circle, vars->data);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
	}
		if(keycode == 88) // tecla 6
	{
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->circle->eje_x = vars->circle->eje_x  + 10;
		vars->data->img = mlx_new_image(vars->mlx, 800, 600);
		ft_putcircle(vars->circle, vars->data);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);	
	}
	if(keycode == 86) // tecla 2
	{
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->circle->eje_x = vars->circle->eje_x  - 10;
		vars->data->img = mlx_new_image(vars->mlx, 800, 600);
		ft_putcircle(vars->circle, vars->data);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);	
	}
	if(keycode == 84) // tecla 4
	{
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->circle->eje_y = vars->circle->eje_y  + 10;
		vars->data->img = mlx_new_image(vars->mlx, 800, 600);
		ft_putcircle(vars->circle, vars->data);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);	
	}
	if(keycode == 91) // tecla 8
	{
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->circle->eje_y = vars->circle->eje_y  -10;
		vars->data->img = mlx_new_image(vars->mlx, 800, 600);
		ft_putcircle(vars->circle, vars->data);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);	
	}
	return(0);
}

int	main(void)
{
	t_vars	vars;
		
	vars.circle = malloc (sizeof (t_circle) * 1);
	vars.data = malloc (sizeof (t_data) * 1);
	
	vars.circle->eje_x = 400;
	vars.circle->eje_y = 300;
	vars.circle->radio = 10;
	
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 800, 600, "Hello world!");
	vars.data->img = mlx_new_image(vars.mlx, 800, 600);
	vars.data->addr = mlx_get_data_addr(vars.data->img, &vars.data->bits_per_pixel, &vars.data->line_length, &vars.data->endian);
	
	ft_putcircle(vars.circle, vars.data);	
	
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.data->img, 0, 0);
	
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	
	mlx_hook(vars.mlx_win, 2, 1L<<0, &key_hook_close, &vars);
	
	mlx_loop(vars.mlx);
	return(0);
}
