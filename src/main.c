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
	free(data->piece->y);
	free(data->map->heatmap);
	data->piece->pheight = 0;
	data->piece->pwidth = 0;
	data->piece->x = NULL;
	data->piece->y = NULL;
	data->piece->stars = 0;
	data->map_height = 0;
	data->map_width = 0;
}


int	main(void)
{
	t_data	data;
	t_piece	piece;
	t_map	map;
	int		ret;
	int		i;
	char tmp = 'H';

	
	remove("read_log.txt");
	ret = 1;
	i = 0;
	if (init_data(&data, &piece, &map) == -1)
	{
		print_struct(&data);
		fprintf(data.struct_log, "init data i = %d\n", i);
		return (-1);
	}
	if (read_players_symb(&data) == -1)
	{
		print_struct(&data);
		fprintf(data.struct_log, "players symb i = %d\n", i);
		return (-1);
	}
	if (read_map_size(&data) == -1)
	{
		print_struct(&data);
		fprintf(data.struct_log, "map size i = %d\n", i);
		return (-1);
	}
	if (build_heatmap(&data) == -1)
	{
		print_struct(&data);
		fprintf(data.struct_log, "build heatmap i = %d\n", i);
		return (-1);
	}
	// while (ret >= 0)
	// {
		if (read_map(&data) == -1)
		{
			print_struct(&data);
			fprintf(data.struct_log, "build heatmap i = %d\n", i);
			return (-1);
		}
		if (read_piece_width_height(&data) == -1)
		{
			print_struct(&data);
			fprintf(data.struct_log, "read piece width i = %d\n", i);
			return (-1);
		}
		if (build_piece(&data) == -1)
		{
			print_struct(&data);
			fprintf(data.struct_log, "build piece i = %d\n", i);
			return (-1);
		}
		if (read_piece_shape(&data) == -1)
		{
			print_struct(&data);
			fprintf(data.struct_log, "read piece shape i = %d\n", i);
			return (-1);
		}
		ret = place_piece(&data);
		print_struct(&data);
		read(data.map_test, &tmp, 1);
		dprintf(2, "%c", tmp);
		// read(data.map_test, &tmp, 1);
		// dprintf(2, "%c", tmp);
		init_ingame(&data);
		print_struct(&data);
		// }
		//
		// read(0, &tmp, 1);
		// fprintf(data.read_log, "%c", tmp);
		return (0);
}
