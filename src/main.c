/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:31:40 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/06 19:31:41 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

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
	data->side_touch = 0;
}

int	map_operations(t_data *data)
{
	if (read_map_size(data) == -1)
		return (-1);
	if (build_heatmap(data) == -1)
		return (-1);
	if (read_map(data) == -1)
		return (-1);
	if (data->contact)
		update_heatmap(data, 0, 0);
	return (0);
}

int	piece_operations(t_data *data)
{
	if (read_piece_width_height(data) == -1)
		return (-1);
	if (build_piece(data) == -1)
		return (-1);
	if (read_piece_shape(data, 0) == -1)
		return (-1);
	build_piece_heatmap(data);
	if (place_iterative(data, 0, 0, -1) == -1)
		return (-1);
	return (0);
}

int	main(void)
{
	t_data	data;
	t_piece	piece;
	t_map	map;
	int		ret;
	int		i;

	ret = 1;
	i = 0;
	if (init_data(&data, &piece, &map) == -1)
		return (-1);
	if (read_players_symb(&data) == -1)
		return (-1);
	while (ret >= 0)
	{
		if (map_operations(&data) == -1)
			return (-1);
		if (piece_operations(&data) == -1)
			return (-1);
		init_ingame(&data);
		i++;
	}
	return (0);
}
