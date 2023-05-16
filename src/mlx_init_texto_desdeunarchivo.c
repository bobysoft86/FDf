/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roberodr <roberodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:43:15 by roberodr          #+#    #+#             */
/*   Updated: 2023/04/19 09:27:36 by roberodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>


#define MAX_LINES 100

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int     key_hook(int keycode, t_vars *vars)
{
    if (keycode == 53)  // tecla Esc
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}

int main(int argc, char **argv)
{

	t_vars vars;
	void *img;
	int  	fp;
	char	*line;
	int 	y = 0;



 if (argc != 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        exit(1);
    }
	
    fp = open(argv[1], O_RDONLY);

	

    if (fp < 0)
    {
        printf("Error: could not open file %s\n", argv[1]);
        exit(1);
    }
    
	line = malloc(200 * sizeof(char));
	vars.mlx = mlx_init();
     vars.win = mlx_new_window(vars.mlx, 640, 480, "esto es una caca");
    y = 50;
    if ((read(fp, line,10)))
    {
        mlx_string_put(vars.mlx, vars.win, 50, y, 0xff00ff0f, line);
        y += 20;
	//printf("line es %d", mlx_string_put(vars.mlx, vars.win, 50, y, 0x000000FF, line));
    }
	img = mlx_new_image(vars.mlx, 1920, 1080);
	 mlx_string_put(vars.mlx, vars.win, 50, y, 0xff00ff0f, "fuera de linea");
    close(fp);
	mlx_hook(vars.win, 2, 1L<<0, &key_hook, &vars);
    mlx_loop(vars.mlx);
    return (0);
}