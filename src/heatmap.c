/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heatmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:42:18 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/07 16:42:20 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int	build_heatmap(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->map->heatmap = (int **)malloc(sizeof(int *) * data->map_height);
	if (!data->map->heatmap)
		return (-1);
	while (y < data->map_height)
	{
		data->map->heatmap[y] = (int *)malloc(sizeof(int) * data->map_width);
		if (!data->map->heatmap[y])
			return (-1);
		while (x < data->map_width)
		{
			data->map->heatmap[y][x] = -1;
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

// int	check_smallest(t_data *data, int x, int y)
// {
// 	int	x_off;
// 	int	y_off;
// 	int	smallest;

// 	smallest = 10000000;
// 	x_off = -1;
// 	y_off = -1;
// 	while (y_off < 2)
// 	{
// 		while (x_off < 2)
// 		{
// 			if (x + x_off >= 0 && x + x_off < data->map_width
// 				&& y + y_off >= 0 && y + y_off < data->map_height)
// 			{
// 				if (data->map->heatmap[y + y_off][x + x_off] > 0
// 					&& data->map->heatmap[y + y_off][x + x_off] < smallest)
// 					smallest = data->map->heatmap[y + y_off][x + x_off];
// 			}
// 			x_off++;
// 		}
// 		x_off = -1;
// 		y_off++;
// 	}
// 	printf("Smallest = %d\n", smallest);
// 	if (smallest == 10000000)
// 		return (fill_heatmap(data, x, y));
// 	return (smallest);
// }

void	set_around_enemy(t_data *data, int x, int y, int steps)
{
	int	x_off;
	int	y_off;

	x_off = -1;
	y_off = -1;
	while (y_off < 2)
	{
		while (x_off < 2)
		{
			if (x + x_off < data->map_width && x + x_off >= 0
			&& 	y + y_off < data->map_height && y + y_off >= 0)
			{
				if ((x_off != 0 || y_off != 0) && data->map->heatmap[y + y_off][x + x_off] != 1)
					data->map->heatmap[y + y_off][x + x_off] = steps + 1;
			}
			x_off++;
		}
		x_off = -1;
		y_off ++;
	}
}

int update_heatmap(t_data *data)
{
	int	x;
	int	y;
	int	steps;

	x = 0;
	y = 0;
	steps = 1;
	while (y < data->map_height && y > -1)
	{
		while (x < data->map_width && x > -1)
		{
			if (data->map->heatmap[y][x] == steps)
			{
				set_around_enemy(data, x , y, steps);
				steps++;
				return (1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

int	insert_piece(t_data *data, int x, int y)
{
	int	overlap;
	int	i;

	overlap = 0;
	i = 0;
	while (i < data->piece->stars)
	{
		if (y + data->piece->y[i] < data->map_height && x + data->piece->x[i] < data->map_width)
		{
			if (data->map->heatmap[y + data->piece->y[i]][x + data->piece->x[i]] == -1)
				i++;
			else if (data->map->heatmap[y + data->piece->y[i]][x + data->piece->x[i]] == -2)
			{
				i++;
				overlap++;
			}
		}
		else
			break ;
	}
	if (i == data->piece->stars && overlap == 1)
		return (1);
	else
		return (-1);
}

int	place_piece(t_data *data)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	x = 0;
	y = 0;
	while (y < data->map_height)
	{
		// printf("y = %d\n", y);
		// while (i < data->map_width)
		// {
		// 	printf("%d ", data->map->heatmap[y][i]);
		// 	i++;
		// }
		// i = 0;
		// printf("\n");
		while (x < data->map_width)
		{
			if (insert_piece(data, x, y) == 1)
			{
				// printf("RETURN 1\n");
				printf("%d %d", y, x);
				// dprintf(2, "%d %d\n", y, x);
				return (0);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (-1);
}