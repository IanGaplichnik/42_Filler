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

/* Function, initializing data. All pointers are set to NULL to avoid double
free(). Integers set to requiered values. */
int	init_data(t_data *data, t_piece *piece, t_map *map)
{
	data->map_height = 0;
	data->map_width = 0;
	data->piece = piece;
	data->piece->p_height = 0;
	data->piece->p_width = 0;
	data->piece->x = NULL;
	data->piece->y = NULL;
	data->piece->stars = 0;
	data->map = map;
	data->map->heatmap = NULL;
	data->map->filled = 0;
	data->map->best_x = -1;
	data->map->best_y = -1;
	data->map->best_value = 100000000;
	data->map->max_value = 0;
	data->ex = -1;
	data->ey = -1;
	data->contact = 0;
	data->priority = 0;
	return (0);
}

/* Initializing data while in game. Arrays are being freed,
some integers being reset. */
void	init_ingame(t_data *data)
{
	free(data->piece->x);
	data->piece->x = NULL;
	free(data->piece->y);
	data->piece->y = NULL;
	data->piece->p_height = 0;
	data->piece->p_width = 0;
	data->piece->stars = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->map->filled = 0;
	data->map->max_value = 0;
	data->map->best_x = -1;
	data->map->best_y = -1;
	data->map->best_value = 100000000;
	data->ex = -2;
	data->ey = -2;
	data->priority = 0;
}

int	ft_abs(double long x)
{
	if (x < 0)
		return (-x);
	return (x);
}
