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
	int	y;
	int	x;

	y = 0;
	if (!data->map->heatmap)
	{
		data->map->heatmap = (int **)malloc(sizeof(int *) * data->map_height);
		if (!data->map->heatmap)
			return (-1);
		while (y < data->map_height)
		{
			x = 0;
			data->map->heatmap[y] = (int *)malloc(sizeof(int)
					* data->map_width);
			if (!data->map->heatmap[y])
				return (-1);
			while (x < data->map_width)
			{
				data->map->heatmap[y][x] = -1;
				x++;
			}
			y++;
		}
	}
	return (0);
}

void	set_around_slot(t_data *data, int x, int y)
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
				&& y + y_off < data->map_height && y + y_off >= 0
				&& (x_off != 0 || y_off != 0)
				&& data->map->heatmap[y + y_off][x + x_off] == -1)
			{
				data->map->heatmap[y + y_off][x + x_off] = data->map->max_value
					+ 1;
				data->map->filled = 0;
			}
			x_off++;
		}
		x_off = -1;
		y_off++;
	}
}

int	update_heatmap(t_data *data, int x, int y)
{
	int	filled;

	filled = 0;
	while (data->map->filled == 0)
	{
		data->map->filled = 1;
		while (y < data->map_height && y > -1)
		{
			while (x < data->map_width && x > -1)
			{
				if (data->map->heatmap[y][x] == data->map->max_value)
					set_around_slot(data, x, y);
				x++;
			}
			x = 0;
			y++;
		}
		y = 0;
		x = 0;
		data->map->max_value++;
	}
	return (1);
}
