/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_squeare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 09:38:20 by roberodr          #+#    #+#             */
/*   Updated: 2023/05/10 13:12:39 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct  s_vars {
   	void	*mlx;
	void	*mlx_win;
}               t_vars;

int     key_hook(int keycode, t_data *data)
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

	printf("%d --- %d --- %p --- %p\n", data->line_length, data->bits_per_pixel, data->addr, data);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_putsquare ( int x, int y, t_data img)
{
	int tmp1;
	int tmp2;
	int j = x + 200;
	int k = y + 200;
	tmp1 = x;
	tmp2 = y;
while (x < j)
		{
			my_mlx_pixel_put(&img, x, y, 0x00FFF00);
			x++;
		}
	while(y < k)
		{
			my_mlx_pixel_put(&img, tmp1, y, 0x00FFF00);
			y++;
		}
	 		y = tmp2 ;
	while(y < k )
		{
			my_mlx_pixel_put(&img, x, y, 0x00FFF00);
			y++;
		} 
			x = tmp1 ;
	while (x < j )
		{
			my_mlx_pixel_put(&img, x, k, 0x00FFF00);
			x++;
		}
	
}

int	main(void)
{
	t_data	img;
	t_vars	vars;
	
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 800, 600, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	ft_putsquare(600, 250, img);
	
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 1L<<0, &key_hook, &vars);
	mlx_loop(vars.mlx);
	return(0);
}
