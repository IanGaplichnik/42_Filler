/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:12:24 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/06 19:12:41 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	print_struct(t_data *data)
{
	int i;

	i = 0;
	fprintf(data->struct_log, "enemy = %c\nplayer = %c\n", data->enemy, data->player);
	fprintf(data->struct_log, "map_height = %d\nmap_width= %d\n", data->map_height, data->map_width);
	fprintf(data->struct_log, "piece_height = %d\npiece_width= %d\n", data->piece->pheight, data->piece->pwidth);
	fprintf(data->struct_log, "piece_x_coord = ");
	while (i < data->piece->stars)
	{
		fprintf(data->struct_log, "%d ", data->piece->x[i]);
		i++;
	}
	i = 0;
	fprintf(data->struct_log, "\npiece_y_coord = ");
	while (i < data->piece->stars)
	{
		fprintf(data->struct_log, "%d ", data->piece->y[i]);
		i++;
	}
	fprintf(data->struct_log, "\nstars = %d", data->piece->stars);
	fprintf(data->struct_log, "\n\n");
	// fclose(file);
}

int	init_data(t_data *data, t_piece *piece, t_map *map)
{
	data->read_log = fopen("read_log.txt", "a+");
	data->struct_log = fopen("struct_log.txt", "a+");
	data->heat_log = fopen("heat_log.txt", "a+");
	data->map_test = open("map_ex.txt", O_RDWR);
	data->map_test = 0; //to test with stdout
	data->map_height = 0;
	data->map_width = 0;
	data->piece = piece;
	data->piece->pheight = 0;
	data->piece->pwidth = 0;
	data->piece->x = NULL;
	data->piece->y = NULL;
	data->piece->stars = 0;
	data->map = map;
	data->map->heatmap = NULL;
	return (0);
}

void	print_heatmap(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			fprintf(data->heat_log, "%3d ", data->map->heatmap[y][x]);
			x++;
		}
		fprintf(data->heat_log, "\n");
		x = 0;
		y++;
	}
	fprintf(data->heat_log, "\n\n");
}