/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:38:20 by roberodr          #+#    #+#             */
/*   Updated: 2023/04/25 13:56:18 by roberodr         ###   ########.fr       */
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
typedef struct s_square{
	int x;
	int y;
}		t_square;
typedef struct  s_vars {
   	void	*mlx;
	void	*mlx_win;
	t_data	*data;
	t_square *square;
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

void ft_putsquare ( t_square *square, t_data *img)
{
	int tmp1;
	int tmp2;
	int j = square->x + 150;
	int k = square->y + 150;
	
	tmp1 = square->x;
	tmp2 = square->y;
	
	 
	 
	while (square->x < j)
		{
			my_mlx_pixel_put(img, square->x, square->y, 0x00FFF00);
			square->x++;
		}
 	while(square->y < k)
 		{
 			my_mlx_pixel_put(img, tmp1, square->y, 0x00FFF00);
 			square->y++;
 		}
 	 		square->y = tmp2 ;
 	while(square->y < k )
		{
			my_mlx_pixel_put(img, square->x, square->y, 0x00FFF00);
			square->y++;
		} 
			square->x = tmp1 ;
	while (square->x < j )
		{
			my_mlx_pixel_put(img, square->x, k, 0x00FFF00);
			square->x++;
		}
}

int key_hook(int keycode, t_vars *vars)
{
if(keycode == 91) // keypad 8
	{
    mlx_destroy_image(vars->mlx, vars->data->img);
	//vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
    int centerX = vars->square->x + 150;
    int centerY = vars->square->y + 150;
    double angle = 0.4; // incremento del ángulo de rotación
    for  (int i = vars->square->x; i < centerX; i++)
    {
       for (int j = vars->square->y; j < centerY; j++)
        {
            double newX = centerX + (i - centerX) * cos(angle) - (j - centerY) * sin(angle);
            double newY = centerY + (i - centerX) * sin(angle) + (j - centerY) * cos(angle);
			printf("%d\n", centerY );
			printf("%d\n", centerX );
            int color = 0x00FFF00; // color verde
            my_mlx_pixel_put(vars->data, (int)newX , (int)newY , color);
        }
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
}
	return(0);
}

int	main(void)
{
	
	t_vars	vars;
	vars.square = malloc (sizeof (t_square) * 1);
	vars.data = malloc (sizeof (t_data) * 1);
	
	vars.square->x = 600;
	vars.square->y = 600;
	
	
	
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "Square rotation");
	vars.data->img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.data->addr = mlx_get_data_addr(vars.data->img, &vars.data->bits_per_pixel, &vars.data->line_length, &vars.data->endian);
	
	
	ft_putsquare(vars.square, vars.data);
	
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.data->img, 0, 0);
	
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	
	mlx_hook(vars.mlx_win, 2, 1L<<0, &key_hook_close, &vars);
	
	mlx_loop(vars.mlx);
	return(0);
}
