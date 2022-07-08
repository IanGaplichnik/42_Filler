/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:17:55 by igaplich          #+#    #+#             */
/*   Updated: 2022/07/06 19:18:03 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int	read_piece_width_height(t_data *data)
{
	char	tmp;

	tmp = '[';
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		if (read(data->map_test, &tmp, 1) < 1)
			return (-1);
		fprintf(data->read_log, "%c", tmp);
	}
	if (tmp >= '0' && tmp <= '9')
		mark_width_height((&data->piece->pheight), data, &tmp);
	while (tmp != '\0' && (tmp < '0' || tmp > '9'))
	{
		if (read(data->map_test, &tmp, 1) < 1)
			return (-1);
		fprintf(data->read_log, "%c", tmp);
	}
	if (tmp >= '0' && tmp <= '9')
		mark_width_height(&data->piece->pwidth, data, &tmp);
	return (0);
}

int	build_piece(t_data *data)
{
	int	arr_size;

	arr_size = data->piece->pheight * data->piece->pwidth;
	data->piece->x = (int *)malloc(sizeof(int) * arr_size);
	if (!data->piece->x)
		return (-1);
	data->piece->y = (int *)malloc(sizeof(int) * arr_size);
	if (!data->piece->y)
	{
		free(data->piece->x);
		return (-1);
	}
	return (0);
}

int	read_piece_shape(t_data *data)
{
	char	tmp;
	int		x;
	int		y;
	int		i;

	x = -1;
	y = 0;
	i = 0;
	tmp = '[';
	if (read(data->map_test, &tmp, 1) < 0)
		return (-1);
	fprintf(data->read_log, "%c", tmp);
	while (y < data->piece->pheight)
	{
		while (x < data->piece->pwidth) // test with vm
		// while (x < data->piece->pwidth - 1) //for own test
		{
			if (read(data->map_test, &tmp, 1) < 0)
				return (-1);
			x++;
			fprintf(data->read_log, "%c", tmp);
			if (tmp == '*')
			{
				data->piece->x[i] = x;
				data->piece->y[i] = y;
				i++;
			}
		}
		x = -1;
		y++;
	}
	data->piece->stars = i;
	return (0);
}
