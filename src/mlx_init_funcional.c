/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:10:25 by roberodr          #+#    #+#             */
/*   Updated: 2023/05/12 10:09:56 by roberodr         ###   ########.fr       */
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
	int pos_y;
	int pos_z;
	int tmp_pos;
	int tmp_pos2;
	int iso_x;
	int iso_y;
	int  space;
	int ang;
	char *map;
}	t_matrix;


typedef struct  s_vars {
   	void	*mlx;
	void	*mlx_win;
	char	*argv;
	
	t_data *data;
	t_matrix *matrix;
	
}               t_vars;

int close_window(void *param) 
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_destroy_window(vars->mlx, vars->mlx_win);

	exit(0);
}

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

void ft_print_line2(int x, int y, int a, int b, t_vars *vars)
{

	while (y >= b)
	{
		my_mlx_pixel_put(vars->data,x* cos(120), y * sin(120), 0x0FFFF00);
		y--;
	}
	while (x >= a)
	{
		my_mlx_pixel_put(vars->data, x* cos(120),y * sin(120), 0x0FFFF00);
		x--;
	}
}

void ft_print_line(int x, int y, int a, int b, t_vars *vars)
{

	while (y <= b)
	{
		my_mlx_pixel_put(vars->data,(x  - y ) * cos(120), (x + y) * sin(120), 0x0FFFF00);
		y++;
	}
	while (x <= a)
	{
		
		my_mlx_pixel_put(vars->data, ((x  - y ) * cos(120)), ((x + y) * sin(120)), 0x0FFFF00);
		x++;
	}
}


// void ft_putmatrix(int largo, int alto, t_data *img, t_matrix *matrix)
// {
// 	int x = 0;
// 	int j = 0;

// 	while ( j < alto -1)
// 	{
// 		while(x < largo  )
// 		{
// 			my_mlx_pixel_put(img, matrix->pos_x, matrix->pos_y, 0x00FFF00);
// 			ft_print_line(matrix->tmp_pos, matrix->pos_y, matrix->pos_x, matrix->pos_y, img); //lineas verticales 
// 			ft_print_line(matrix->pos_x, matrix->tmp_pos2 , matrix->pos_x, matrix->pos_y, img); //lineas horizontales
// 			matrix->tmp_pos = matrix->pos_x;
// 			matrix->pos_x = matrix->pos_x + matrix->space;
// 			x++;
// 		}
// 		x = 0;
// 		matrix->pos_x = 10;
// 		//my_mlx_pixel_put(img, matrix->pos_x, matrix->pos_y, 0x00FFF00);
// 		 //matrix->tmp_pos2 = matrix->pos_y;
// 		j++;
// 		 matrix->pos_y = matrix->pos_y + matrix->space;
// 	}
// }


int ft_read_map(char *argv, t_vars *vars)
{
	char	*line;
	char	*line_parsed;
	int		fd;
	int i;
	int j;
	j=0;
	i = 0;
	
	vars->matrix->map = malloc (sizeof (char *) * 1 );
	line_parsed = malloc (sizeof (char *) * 1 );
	
	fd = open(argv, O_RDONLY);
	while(fd)
	{
	
		line = get_next_line(fd);
 		if (!line)
 			return (0);
		while(line[i] != '\0')
		{
			if (ft_isdigit(line[i]) || line [i] == ' ' || line[i] == '\n' || (line[i] == '-' && ft_isdigit(line[i+1])))
			{
				vars->matrix->map[j++] = line[i];
				vars->matrix->map = realloc(vars->matrix->map,(j+1) * sizeof(char));
			}
			i++;
		}
		
		i =0;
		free(line);
		vars->matrix->map[j]= '\0';
		//printf("%s <%lu>\n",line, strlen(line));		
		//vars->matrix->map = ft_strjoin(vars->matrix->map, line_parsed);
		//printf("%s <%lu>\n", vars->matrix->map, strlen(vars->matrix->map) );
		//vars->matrix->map = ft_split(line, '\n');
		//printf("Line %d for fd %d: %s <%zu>\n", vars->matrix->alto, fd, *vars->matrix->map, strlen(*vars->matrix->map));
		//free(line);
	}
	return (1);
}

//copia de la version funcional de read map antes preparar la print map
// anterior read map 
void ft_print_map(t_vars *vars)
{
	int i;
	int up_x;
	int up_y;
	

	
	i = 0;
	
	//vars->matrix->tmp_pos = vars->matrix->pos_x;
	while(vars->matrix->map[i] != '\0')	
	{		
		if (vars->matrix->map[i] == '0') 
		{
			
			my_mlx_pixel_put(vars->data, (vars->matrix->pos_x  - vars->matrix->pos_y ) * cos(120),(vars->matrix->pos_x + vars->matrix->pos_y) * sin(120), 0x00FFF00);
			 printf("down x:%f y:%f\n", (vars->matrix->pos_x  - vars->matrix->pos_y ) * cos(vars->matrix->ang), (vars->matrix->pos_x + vars->matrix->pos_y) * sin(vars->matrix->ang));
			ft_print_line(vars->matrix->pos_x - vars->matrix->space  , vars->matrix->pos_y, vars->matrix->pos_x, vars->matrix->pos_y, vars);//lineas verticales 
			//ft_print_line(vars->matrix->pos_x, vars->matrix->pos_y - vars->matrix->space, vars->matrix->pos_x, vars->matrix->pos_y, vars);//lineas horizontales
			vars->matrix->pos_x = vars->matrix->pos_x + vars->matrix->space;
			while(ft_isdigit(vars->matrix->map[i]))
				i++;
		}
		if (vars->matrix->map[i] > '0' && vars->matrix->map[i] <= '9') 
		{
			up_x = vars->matrix->pos_x - atoi(vars->matrix->map + i);
			up_y = vars->matrix->pos_y - atoi(vars->matrix->map + i);
			my_mlx_pixel_put(vars->data, (up_x  - up_y ) * cos(120), (up_x + up_y) * sin(120), 0x00FFF00);
			 printf("UP x:%f y:%f\n",(up_x  - up_y ) * cos(120), (up_x + up_y) * sin(120));			
			
			 //ft_print_line2( (vars->matrix->pos_x  - vars->matrix->pos_y ) , (vars->matrix->pos_x + vars->matrix->pos_y), (up_x  - up_y ), (up_x + up_y) ,  vars);
			
			// ft_print_line(up_x - vars->matrix->space, up_y, up_x, up_y, vars);//lineas verticales 
			// ft_print_line(up_x, up_y - vars->matrix->space , up_x, up_y, vars);//lineas horizontales
			
			vars->matrix->pos_x = vars->matrix->pos_x + vars->matrix->space;
			while(ft_isdigit(vars->matrix->map[i]))
				i++;
		}
		 if (vars->matrix->map[i] == ' ')
		 	i++;
		if (vars->matrix->map[i] == '-')
		{
			i++;
			up_x = vars->matrix->pos_x + atoi(vars->matrix->map + i);
			up_y = vars->matrix->pos_y + atoi(vars->matrix->map + i);
			//my_mlx_pixel_put(vars->data, (up_x  - up_y ) * cos(120), (up_x + up_y) * sin(120), 0x00FFF00);
			printf("UP x:%f y:%f\n",(up_x  - up_y ) * cos(120), (up_x + up_y) * sin(120));			
			
			//ft_print_line2( (vars->matrix->pos_x  - vars->matrix->pos_y ) * cos(120), (vars->matrix->pos_x + vars->matrix->pos_y) * sin(120), (up_x  - up_y ) * cos(120), (up_x + up_y) * sin(120),  vars);
			
			//ft_print_line(up_x - vars->matrix->space, up_y, up_x, up_y, vars);//lineas verticales 
			//ft_print_line(up_x, up_y - vars->matrix->space , up_x, up_y, vars);//lineas horizontales
			
			vars->matrix->pos_x = vars->matrix->pos_x + vars->matrix->space;
			while(ft_isdigit(vars->matrix->map[i]))
				i++;
		}
		if (vars->matrix->map[i] == '\n')
			{
			i++;
			vars->matrix->pos_x = vars->matrix->tmp_pos;
			vars->matrix->pos_y = vars->matrix->pos_y + vars->matrix->space;
			}
	}
	//vars->matrix->pos_y = vars->matrix->pos_y  + vars->matrix->space;
	//vars->matrix->pos_x = vars->matrix->tmp_pos;
}


int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 69) // tecla +
	{
		vars->matrix->pos_x = 900;
		vars->matrix->pos_y = 1;
				
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->matrix->space = vars->matrix->space * 2.3;
			
		vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
		ft_print_map(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
	}
	if (keycode == 78) //tecla -
	{
		vars->matrix->pos_x = 900;
		vars->matrix->pos_y = 1;
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->matrix->space = vars->matrix->space / 1.05;
		vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
		ft_print_map(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
	}
	if (keycode == 88)
	{
		vars->matrix->pos_x = 900;
		vars->matrix->pos_y = 1;
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->matrix->pos_x = vars->matrix->pos_x * 1.3;
		vars->matrix->pos_y = vars->matrix->pos_y / 0.9;
		vars->data->img = mlx_new_image(vars->mlx, 1920, 1080);
		ft_print_map(vars);
		mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->data->img, 0, 0);
		
	}
	
	
  	return(0);
}
int	main(int argc, char **argv)
{
	t_vars	vars;
	vars.argv = argv[1];
		
	if (argc != 2)
		return (0);
	vars.data = malloc (sizeof (t_data) * 1);
	vars.matrix = malloc (sizeof (t_matrix) * 1);
	vars.matrix->ang = 120;
	vars.matrix->alto = 1;
	vars.matrix->largo = 0;
	vars.matrix->pos_x = 900;     
	vars.matrix->pos_y = 1;
	vars.matrix->tmp_pos = vars.matrix->pos_x;
	vars.matrix->tmp_pos2 = vars.matrix->pos_y;
	vars.matrix->space =  2;
	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "pillar mapa");
	vars.data->img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.data->addr = mlx_get_data_addr(vars.data->img, &vars.data->bits_per_pixel, &vars.data->line_length, &vars.data->endian);
	ft_read_map(argv[1], &vars);
	ft_print_map(&vars);
	mlx_put_image_to_window(vars.mlx, vars.mlx_win, vars.data->img, 0, 0);
	mlx_key_hook(vars.mlx_win, key_hook, &vars);
	mlx_hook(vars.mlx_win, 2,0, &key_hook_close, &vars);
	mlx_hook(vars.mlx_win, 17, 0, &close_window, &vars);
	mlx_loop(vars.mlx);
	return(0);
}
