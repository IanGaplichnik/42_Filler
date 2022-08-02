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

/* 
 * Function, calling different map operations.
 * Reading map, allocating arrays of map size 
 * and building heat map happen here
 */
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

/* Performing operations with the piece,
 * which algorithm will insert in the map. Reading
 * it, converting to the required format happen here.
 */
int	piece_operations(t_data *data)
{
	if (read_piece_width_height(data) == -1)
		return (-1);
	if (build_piece(data) == -1)
		return (-1);
	if (read_piece_shape(data, 0) == -1)
		return (-1);
	if (place_piece(data, 0, 0, -1) == -1)
		return (-1);
	return (0);
}

/* 
 * Main function, running as long, as required text
 * is in correct format and exists. Loop stops, if whether there's
 * nothing to read or formatting is wrong. Players symbols are only
 * read once, due to the format of the input.
 */
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
		ret = map_operations(&data);
		if (ret == -1)
			return (-1);
		ret = piece_operations(&data);
		if (ret == -1)
			return (-1);
		init_ingame(&data);
		i++;
	}
	return (0);
}
