/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_piece.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:05:23 by macbook           #+#    #+#             */
/*   Updated: 2022/07/12 16:05:28 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"
#include <math.h>

int	mark_best_piece(t_data *data, int x, int y, t_insert c)
{
	if (c.i == data->piece->stars && c.overlap == 1
		&& data->map->best_value > c.lowest)
	{
		data->map->best_x = x;
		data->map->best_y = y;
		data->map->best_value = c.lowest;
		return (1);
	}
	return (-1);
}

int	insert_before(t_data *data, int x, int y)
{
	t_insert	c;

	c.lowest = 1000000;
	c.overlap = 0;
	c.i = 0;
	while (c.i < data->piece->stars && c.overlap < 2)
	{
		c.x_act = x + data->piece->x[c.i];
		c.y_act = y + data->piece->y[c.i];
		if (c.y_act < data->map_height && c.x_act < data->map_width)
		{
			if (abs(abs(data->ex - (c.x_act))
					+ abs(data->ey - (c.y_act))) < c.lowest)
				c.lowest = abs(abs(data->ex - (c.x_act))
						+ abs(data->ey - (c.y_act)));
			if (data->map->heatmap[c.y_act][c.x_act] == -2)
				c.overlap++;
			else if (data->map->heatmap[c.y_act][c.x_act] == 0)
				return (-1);
			c.i++;
		}
		else
			return (-1);
	}
	return (mark_best_piece(data, x, y, c));
}

void	check_around(t_data *data, int x, int y, t_insert *c)
{
	int x_off;
	int	y_off;
	int	touch_enemy;
	int	side;

	x_off = -1;
	y_off = -1;
	if (x == 0 || x == data->map_width - 1 || y == 0 || y == data->map_height - 1)
		c->side = 1;
	while (y_off < 2)
	{
		while (x_off < 2)
		{
			if (x + x_off < data->map_width && x + x_off >= 0
				&& y + y_off < data->map_height && y + y_off >= 0)
			{
				if (data->map->heatmap[y + y_off][x + x_off] == 0)
					c->touch_enemy = 1;
			}
			x_off++;
		}
		x_off = -1;
		y_off++;
	}
	if (c->side && c->touch_enemy)
		c->priority = 1;
}

int	insert_after(t_data *data, int x, int y)
{
	t_insert	c;

	c.lowest = 100000;
	c.overlap = 0;
	c.i = 0;
	c.priority = 0;
	while (c.i < data->piece->stars && c.overlap < 2)
	{
		c.x_act = x + data->piece->x[c.i];
		c.y_act = y + data->piece->y[c.i];
		check_around(data, c.x_act, c.y_act, &c);
		if (c.y_act < data->map_height && c.x_act < data->map_width)
		{
			if (data->map->heatmap[c.y_act][c.x_act] == -2)
				c.overlap++;
			else if (data->map->heatmap[c.y_act][c.x_act] == 0)
				return (-1);
			else if (data->map->heatmap[c.y_act][c.x_act] > 0
				&& data->map->heatmap[c.y_act][c.x_act] < c.lowest)
					c.lowest = data->map->heatmap[c.y_act][c.x_act];
			c.i++;
		}
		else
			return (-1);
	}
	return (mark_best_piece(data, x, y, c));
}

void	check_contact(t_data *data, int x, int y)
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
				&& y + y_off < data->map_height && y + y_off >= 0)
			{
				if (data->map->heatmap[y + y_off][x + x_off] == 0)
					data->contact = 1;
			}
			x_off++;
		}
		x_off = -1;
		y_off++;
	}
}

int	place_iterative(t_data *data, int x, int y, int i)
{
	while (y < data->map_height)
	{
		while (x < data->map_width)
		{
			if (!data->contact)
				insert_before(data, x, y);
			else
				insert_after(data, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	if (data->map->best_x != -1 && data->map->best_y != -1)
	{
		while (!data->contact && ++i < data->piece->stars)
			check_contact(data, data->map->best_x + data->piece->x[i],
				data->map->best_y + data->piece->y[i]);
		ft_printf("%d %d\n", data->map->best_y, data->map->best_x);
		return (1);
	}
	ft_printf("%d %d\n", 0, 0);
	return (-1);
}
