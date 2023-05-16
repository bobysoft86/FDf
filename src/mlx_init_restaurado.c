/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:10:25 by roberodr          #+#    #+#             */
/*   Updated: 2023/05/05 10:51:28 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "mlx.h"
# include "../libraries/clift/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct	s_matrix{
	int alto;
	int largo;
	int pos_x;
	int pos_y ;
	int pos_z;
	int tmp_pos;
	int tmp_pos2;
	int space;
}	t_matrix;


typedef struct  s_vars {
   	void	*mlx;
	void	*mlx_win;
	
	t_data *data;
	t_matrix *matrix;
	
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

void ft_print_line(int x, int y, int a, int b, void *img)
{

	while (y < b)
		{
			my_mlx_pixel_put(img, x, y, 0x0FFFF00);
			y++;
		}
	while (x < a)
	{
		
		my_mlx_pixel_put(img, x, y, 0x0FFFF00);
		x++;
	}
}


void ft_putmatrix(int largo, int alto, t_data *img, t_matrix *matrix)
{
	int x = 0;
	int j = 0;

	while ( j < alto -1)
	{
		while(x < largo  )
		{
			my_mlx_pixel_put(img, matrix->pos_x, matrix->pos_y, 0x00FFF00);
			ft_print_line(matrix->tmp_pos, matrix->pos_y, matrix->pos_x, matrix->pos_y, img); //lineas verticales 
			ft_print_line(matrix->pos_x, matrix->tmp_pos2 , matrix->pos_x, matrix->pos_y, img); //lineas horizontales
			matrix->tmp_pos = matrix->pos_x;
			matrix->pos_x = matrix->pos_x + matrix->space;
			x++;
		}
		x = 0;
		matrix->pos_x = 10;
		//my_mlx_pixel_put(img, matrix->pos_x, matrix->pos_y, 0x00FFF00);
		 //matrix->tmp_pos2 = matrix->pos_y;
		j++;
		 matrix->pos_y = matrix->pos_y + matrix->space;
	}
}

int key_hook(int keycode, t_vars *vars)
{
	 
	if (keycode == 69) // tecla +
		{
			vars->matrix->pos_x = 10;
			vars->matrix->pos_y = 10;		
			mlx_destroy_image(vars->mlx, vars->data->img);
			vars->matrix->space = vars->matrix->space * 1.1;
			vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
			ft_putmatrix(vars->matrix->largo, vars->matrix->alto, vars->data,vars->matrix);
			mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
		}
	if (keycode == 78) //tecla -
		{
			vars->matrix->pos_x = 10;
			vars->matrix->pos_y = 10;	
			mlx_destroy_image(vars->mlx, vars->data->img);
			vars->matrix->space = vars->matrix->space / 1.05;
			vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
			ft_putmatrix(vars->matrix->largo, vars->matrix->alto, vars->data,vars->matrix);
			mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
		}
			  	return(0);
}

int ft_read_map(char *argv, t_vars *vars)
{
	char	*line;
	char	**map = NULL;
	int		fd;
	
			
	fd = open(argv, O_RDONLY);
	while(vars->matrix->alto)
	{
		line = get_next_line(fd);
 		if (!line)
 			return (0);
 		
		//printf("Line %d for fd %d: %s <%zu>\n", vars->matrix->alto, fd, line, strlen(line));
		map = ft_split(line, ' ' );
		printf("%lu\n", strlen(*map));
		
		free(line);
 		vars->matrix->alto++;
		vars->matrix->largo = strlen(line);
		//ft_putmatrix(vars->matrix->largo, vars->matrix->alto, vars->data, vars->matrix);
	}
	vars->matrix->alto--;
	return (1);
}
int	main(int argc, char **argv)
{
	t_vars	vars;
		
		if (argc != 2)
			return (0);

	vars.data = malloc (sizeof (t_data) * 1);
	vars.matrix = malloc (sizeof (t_matrix) * 1);
	
	vars.matrix->alto = 1;
	vars.matrix->largo = 0;
	vars.matrix->pos_x = 10;
	vars.matrix->pos_y = 10;
	vars.matrix->tmp_pos = vars.matrix->pos_x;
	vars.matrix->tmp_pos2 = vars.matrix->pos_y;
	vars.matrix->space =  50;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "pillar mapa");
	vars.data->img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.data->addr = mlx_get_data_addr(vars.data->img, &vars.data->bits_per_pixel, &vars.data->line_length, &vars.data->endian);

	ft_read_map(argv[1],&vars);
	ft_putmatrix(vars.matrix->largo, vars.matrix->alto, vars.data, vars.matrix);
			
	
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.data->img, 0, 0);
	
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	
	mlx_hook(vars.mlx_win, 2, 1L<<0, &key_hook_close, &vars);
	
	mlx_loop(vars.mlx);
	return(0);
}
