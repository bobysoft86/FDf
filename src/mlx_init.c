# include "mlx.h"
# include "../libraries/clift/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

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
	char **map_parsed;
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
		my_mlx_pixel_put(vars->data, x * cos(120), y * sin(120), 0x0FFFF00);
		y--;
	}
	while (x >= a)
	{
		my_mlx_pixel_put(vars->data, x * cos(120),y * sin(120), 0x0FFFF00);
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

int ft_read_map(char *argv, t_vars *vars)
{
	char	*line;
	char	*line_parsed;
	int		fd;
	int		i;
	int		j;
	j = 0;
	i = 0;
	
	vars->matrix->map_parsed = malloc (sizeof (char **) * 1 );
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
		printf("esto es sin parsear \n%s", vars->matrix->map );
		//printf(" parte entrada \n%s\n", vars->matrix->map);
	}
	return (1);
}

void ft_parse_map(char *map, char **map_parsed)
 {
	//int j = 0;
	int i = 0;

	ft_strlen(map);
	
	
	map_parsed = ft_split(map, ' ');

	while (map_parsed[i] != NULL)
	{
		printf("Esto es el parseado%s\n", map_parsed[i]);
		i++;	
	}
	
}


//copia de la version funcional de read map antes preparar la print map

void ft_print_map(t_vars *vars)
{
	int i;
	int j;
	
	j = 0;
	i = 0;
	
	ft_parse_map(vars->matrix->map, vars->matrix->map_parsed);
	while (vars->matrix->map_parsed[i] != NULL)
	{
		printf("Esto es AAA%s\n", vars->matrix->map_parsed[i]);
		i++;	
	}
	//printf("parte entrada \n%s\n", vars->matrix->map_parsed[i]);
	// while(vars->matrix->map_parsed[i] != NULL )	
	// {
	// 	my_mlx_pixel_put(vars->data, (vars->matrix->pos_x  - vars->matrix->pos_y ) * cos(120),(vars->matrix->pos_x + vars->matrix->pos_y) * sin(120), 0x00FFF00);
	// 	vars->matrix->pos_x = vars->matrix->pos_x + vars->matrix->space;
	// 	//printf("%s", vars->matrix->map_parsed[i] );
	// 	i++;
	// }
	// printf("esto es la len de parse map %d",i);
 }

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == 69) // tecla +
	{
		vars->matrix->pos_x = 900;
		vars->matrix->pos_y = 1;
				
		mlx_destroy_image(vars->mlx, vars->data->img);
		vars->matrix->space = vars->matrix->space * 1.5;
			
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
